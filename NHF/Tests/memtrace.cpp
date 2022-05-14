/*********************************
Memoriaszivargas-detektor
Keszitette: Peregi Tamas, BME IIT, 2011
            petamas@iit.bme.hu
Kanari:     Szeberenyi Imre, 2013.
VS 2012:    Szeberényi Imre, 2015.,
mem_dump:   2016.
memset felszabaditaskor: 2018.
typo:       2019.
poi_check:  2021.
*********************************/

/*definialni kell, ha nem paracssorbol allitjuk be (-DMEMTRACE) */

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef MEMTRACE
#define FROM_MEMTRACE_CPP
#include "memtrace.h"

#define FMALLOC 0
#define FCALLOC 1
#define FREALLOC 2
#define FFREE 3
#define FNEW 4
#define FDELETE 5
#define FNEWARR 6
#define FDELETEARR 7
#define COMP(a,d) (((a)<=3 && (d)<=3) || ((d)==(a)+1))
#define PU(p)   ((char*)p+CANARY_LEN)	// mem pointerbol user poi
#define P(pu)   ((char*)pu-CANARY_LEN)	// user pointerbol mem poi
#define XSTR(s) STR(s)
#define STR(s)  #s
/*******************************************************************/
/* Segedfuggvenyek es egyebek */
/*******************************************************************/
START_NAMESPACE
    static FILE *fperror;
    #ifdef MEMTRACE_TO_MEMORY
    	static const unsigned int CANARY_LEN = 64;
    #else
    	static const unsigned int CANARY_LEN = 0;
    #endif
    static const unsigned char canary_byte1 = 'k';
    static const unsigned char canary_byte2 = 'K';
    static unsigned char random_byte;

	typedef enum {FALSE,TRUE} BOOL;

	static const char * pretty[] = {"malloc(", "calloc(", "realloc(", "free(",
                                        "new", "delete", "new[]", "delete[]"};

	static const char * basename(const char * s) {
		const char *s1,*s2;
		s1 = strrchr(s,'/');
		if(s1==NULL) s1 = s; else s1++;
		s2 = strrchr(s1, '\\');
		if(s2==NULL) s2 = s1; else s2++;
		return s2;
	}

	static char *StrCpy(char ** to, const char * from) {
        	if(from == NULL) {
			*to = NULL;
        	} else {
            		*to = (char*)malloc(strlen(from)+1);
            		if(*to) strcpy(*to, from);
        	}
        	return *to;
	}

	static void *canary_malloc(size_t size, unsigned char data) {
		char *p = (char *)malloc(size+2*CANARY_LEN);
		if (p) {
			memset(p, canary_byte1, CANARY_LEN);
			memset(p+CANARY_LEN, data, size);
			memset(p+CANARY_LEN+size, canary_byte2, CANARY_LEN);
		}
		return p;
	}

	static int chk_canary(void *p, size_t size) {
		unsigned char *pc = (unsigned char*)p;
		unsigned int i;
		for (i = 0; i < CANARY_LEN; i++)
			if (pc[i] != canary_byte1)
				return -1;
		pc += CANARY_LEN+size;
		for (i = 0; i < CANARY_LEN; i++)
			if (pc[i] != canary_byte2)
				return 1;
		return 0;
	}

	typedef struct {
		int f;  /* allocator func */
		int line;
		char * par_txt;
		char * file;
	} call_t;

	static call_t pack(int f, const char * par_txt, int line, const char * file) {
		call_t ret;
		ret.f = f;
		ret.line = line;
		StrCpy(&ret.par_txt, par_txt);
		StrCpy(&ret.file, file);
		return ret;
	}

	static void print_call(const char * msg, call_t call) {
		if(msg) fprintf(fperror, "%s", msg);
		fprintf(fperror, "%s", pretty[call.f]);
		fprintf(fperror, "%s", call.par_txt ? call.par_txt : "?");
		if (call.f <= 3) fprintf(fperror, ")");
		fprintf(fperror," @ %s:", call.file ? basename(call.file) : "?");
		fprintf(fperror,"%d\n",call.line ? call.line : 0);
	}

	/* memoriateruletet dump */
	static void dump_memory(void const *mem, size_t size, size_t can_len, FILE* fp) {
		unsigned char const *m=(unsigned char const *) mem;
		unsigned int s, o;

        if (can_len > 0)
            fprintf(fp, "Dump (addr: %p kanari hossz: %d):\n", m+can_len, (int)can_len);
        else
            fprintf(fp, "Dump: (addr: %p) \n", m);
		size += 2*can_len;
		for (s = 0; s < (size+15)/16; s++) {
			fprintf(fp, "%04x:%c ", s*16, s*16 < can_len || s*16 >= size-can_len ? ' ' : '*');
			for (o = 0; o < 16; o++) {
				if (o == 8) fprintf(fp, " ");
				if (s*16+o < size)
					fprintf(fp, "%02x ", m[s*16+o]);
				else
					fprintf(fp, "   ");
			}
			fprintf(fp, " ");
			for (o = 0; o < 16; o++) {
				if (s*16+o < size)
					fprintf(fp, "%c", isprint(m[s*16+o]) ? m[s*16+o] : '.');
				else
					fprintf(fp, " ");
			}
			fprintf(fp, "\n");
		}
	}

	void mem_dump(void const *mem, size_t size, FILE* fp) {
	    dump_memory(mem, size, 0, fp);
    }

	static BOOL dying;

	static void die(const char * msg, void * p, size_t size, call_t * a, call_t * d) {
		#ifdef MEMTRACE_ERRFILE
            fperror = fopen(XSTR(MEMTRACE_ERRFILE), "w");
        #endif
		fprintf(fperror,"%s\n",msg);
		if (p) {
			fprintf(fperror, "\tPointer:\t%p", PU(p));
			if (size) fprintf(fperror," (%d byte)", (int)size);
			fprintf(fperror,"\n");
		}
		if (a) print_call("\tFoglalas:\t", *a);
		if (d) print_call("\tFelszabaditas:\t", *d);
                if (p) dump_memory(p, size, CANARY_LEN, fperror);

		dying = TRUE;
		exit(120);
	}
	static void initialize();
END_NAMESPACE

/*******************************************************************/
/* MEMTRACE_TO_MEMORY */
/*******************************************************************/

#ifdef MEMTRACE_TO_MEMORY
START_NAMESPACE

	typedef struct _registry_item {
		void * p;    /* mem pointer*/
		size_t size; /* size*/
		call_t call;
		struct _registry_item * next;
	} registry_item;

	static registry_item registry; /*sentinel*/

	static registry_item *find_registry_item(void * p) {
        registry_item *n = &registry;
        for(; n->next && n->next->p != p ; n=n->next);
        return n;
    }

	static void print_registry_item(registry_item * p) {
		if (p) {
			print_registry_item(p->next);
			fprintf(fperror, "\t%p%5d byte ",p->p, (int)p->size);
			print_call(NULL, p->call);
			if(p->call.par_txt) free(p->call.par_txt);
			if(p->call.file) free(p->call.file);
			free(p);
		}
	}

	/* ha nincs hiba, akkor 0-val tér vissza */
	int mem_check(void) {
		initialize();
		if(dying) return  2;    /* címzési hiba */

		if(registry.next) {
			/*szivarog*/
		    #ifdef MEMTRACE_ERRFILE
                fperror = fopen(XSTR(MEMTRACE_ERRFILE), "w");
            #endif
			fprintf(fperror, "Szivargas:\n");
			print_registry_item(registry.next);
			registry.next = NULL;
			return 1;           /* memória fogyás */
		}
        return 0;
	}

	/* Ellenorzi, hogy a pointer regisztralt-e. Ha nem, akkor 0-val tér vissza */
	int poi_check(void *pu) {
	    if (pu == NULL) return 1;
		initialize();
        return find_registry_item(P(pu))->next != NULL;
	}
END_NAMESPACE
#endif/*MEMTRACE_TO_MEMORY*/

/*******************************************************************/
/* MEMTRACE_TO_FILE */
/*******************************************************************/

#ifdef MEMTRACE_TO_FILE
START_NAMESPACE
	static FILE * trace_file;
END_NAMESPACE
#endif

/*******************************************************************/
/* register/unregister */
/*******************************************************************/

START_NAMESPACE
	static int allocated_blks;

    int allocated_blocks() { return allocated_blks; }

	static BOOL register_memory(void * p, size_t size, call_t call) {
		initialize();
		allocated_blks++;
		#ifdef MEMTRACE_TO_FILE
			fprintf(trace_file, "%p\t%d\t%s%s", PU(p), (int)size, pretty[call.f], call.par_txt ? call.par_txt : "?");
			if (call.f <= 3) fprintf(trace_file, ")");
			fprintf(trace_file, "\t%d\t%s\n", call.line, call.file ? call.file : "?");
			fflush(trace_file);
		#endif
		#ifdef MEMTRACE_TO_MEMORY
		{/*C-blokk*/
			registry_item * n = (registry_item*)malloc(sizeof(registry_item));
			if(n==NULL) return FALSE;
			n->p = p;
			n->size = size;
			n->call = call;
			n->next = registry.next;
			registry.next = n;
		}/*C-blokk*/
		#endif

		return TRUE;
	}

	static void unregister_memory(void * p, call_t call) {
		initialize();
		#ifdef MEMTRACE_TO_FILE
                        fprintf(trace_file, "%p\t%d\t%s%s", PU(p), -1, pretty[call.f], call.par_txt ? call.par_txt : "?");
                        if (call.f <= 3) fprintf(trace_file, ")");
			fprintf(trace_file,"\t%d\t%s\n",call.line, call.file ? call.file : "?");
			fflush(trace_file);
		#endif
		#ifdef MEMTRACE_TO_MEMORY
		{ /*C-blokk*/
			registry_item * n = find_registry_item(p);
			if(n->next) {
                allocated_blks--;
				registry_item * r = n->next;
				n->next = r->next;
				if(COMP(r->call.f,call.f)) {
                    int chk = chk_canary(r->p, r->size);
                    if (chk < 0)
						die("Blokk elott serult a memoria:", r->p,r->size,&r->call,&call);
                    if (chk > 0)
                        die("Blokk utan serult a memoria", r->p,r->size,&r->call,&call);
					/*rendben van minden*/
					if(call.par_txt) free(call.par_txt);
					if(r->call.par_txt) free(r->call.par_txt);
					if(call.file) free(call.file);
					if(r->call.file) free(r->call.file);
					memset(PU(r->p), 'f', r->size);
					PU(r->p)[r->size-1] = 0;
					free(r);
				} else {
					/*hibas felszabaditas*/
					die("Hibas felszabaditas:",r->p,r->size,&r->call,&call);
				}
			} else {
				die("Nem letezo, vagy mar felszabaditott adat felszabaditasa:", p, 0,NULL,&call);
			}
		} /*C-blokk*/
		#endif
	}
END_NAMESPACE

/*******************************************************************/
/* C-stílusú memóriakezelés */
/*******************************************************************/

#ifdef MEMTRACE_C
START_NAMESPACE
	void * traced_malloc(size_t size, const char * par_txt, int line, const char * file) {
		void * p;
		initialize();
		p = canary_malloc(size, random_byte);
		if (p) {
			if(!register_memory(p,size,pack(FMALLOC,par_txt,line,file))) {
				free(p);
				return NULL;
			}
		    return PU(p);
		}
        return NULL;
	}

	void * traced_calloc(size_t count, size_t size, const char * par_txt, int line, const char * file) {
		void * p;
		initialize();
                size *= count;
                p = canary_malloc(size, 0);
		if(p) {
			if(!register_memory(p,size,pack(FCALLOC,par_txt,line,file))) {
				free(p);
				return NULL;
			}
		    return PU(p);
		}
		return NULL;
	}

	void traced_free(void * pu, const char * par_txt, int line, const char * file) {
		initialize();
		if(pu) {
			unregister_memory(P(pu), pack(FFREE,par_txt,line,file));
			free(P(pu));
		} else {
			/*free(NULL) eset*/
			#ifdef MEMTRACE_TO_FILE
				fprintf(trace_file,"%s\t%d\t%10s\t","NULL",-1,pretty[FFREE]);
				fprintf(trace_file,"%d\t%s\n",line,file ? file : "?");
				fflush(trace_file);
			#endif
			#ifndef ALLOW_FREE_NULL
			{/*C-blokk*/
				call_t call;
				call = pack(FFREE,par_txt,line,file);
				die("free(NULL) hivasa:",NULL,0,NULL,&call);
			}/*C-blokk*/
			#endif
		}
	}

	void * traced_realloc(void * old, size_t size, const char * par_txt, int line, const char * file) {
		void * p;
        size_t oldsize = 0;
		registry_item * n;
		initialize();

		#ifdef MEMTRACE_TO_MEMORY
        		n = find_registry_item(P(old));
        		if (n) oldsize = n->next->size;
			p = canary_malloc(size, random_byte);
        	#else
        		p = realloc(old, size);
        	#endif
		if (p) {
			/*Ha sikerult a foglalas, regisztraljuk*/
			register_memory(p,size,pack(FREALLOC, par_txt, line,file));
            		if (old) {
				#ifdef MEMTRACE_TO_MEMORY
					int cpsize = 2*CANARY_LEN;
                			if (oldsize < size) cpsize += oldsize;
                			else cpsize += size;
                			memcpy(p, P(old), cpsize);
				#endif
		    			unregister_memory(P(old), pack(FREALLOC, par_txt, line, file));
				#ifdef MEMTRACE_TO_MEMORY
                			free P(old);
            			#endif
            		}
            		return PU(p);
		} else {
	    		return NULL;
        	}
	}

END_NAMESPACE
#endif/*MEMTRACE_C*/

/*******************************************************************/
/* C++-stílusú memóriakezelés */
/*******************************************************************/

#ifdef MEMTRACE_CPP
START_NAMESPACE
	std::new_handler _new_handler;

	void _set_new_handler(std::new_handler h) {
		initialize();
		_new_handler = h;
	}

	static call_t delete_call;
	static BOOL delete_called;

	void set_delete_call(int line, const char * file) {
		initialize();
		delete_call=pack(0,"",line,file); /*func értéke lényegtelen, majd felülírjuk*/
		delete_called = TRUE;
	}

	void * traced_new(size_t size, int line, const char * file, int func) {
		initialize();
		for (;;) {
			void * p = canary_malloc(size, random_byte);
			if(p) {
				register_memory(p,size,pack(func,"",line,file));
				return PU(p);
			}

			if (_new_handler == 0)
				throw std::bad_alloc();

			_new_handler();
		}
	}

	void traced_delete(void * pu, int func) {
		initialize();
		if(pu) {
			/*kiolvasom call-t, ha van*/
			memtrace::call_t call = delete_called ? (delete_call.f=func, delete_call) : pack(func,NULL,0,NULL);
			memtrace::unregister_memory(P(pu),call);
			free(P(pu));
		}
		delete_called=FALSE;
 	}
END_NAMESPACE

void * operator new(size_t size, int line, const char * file) THROW_BADALLOC {
	return memtrace::traced_new(size,line,file,FNEW);
}

void * operator new[](size_t size, int line, const char * file) THROW_BADALLOC {
	return memtrace::traced_new(size,line,file,FNEWARR);
}

void * operator new(size_t size) THROW_BADALLOC {
	return memtrace::traced_new(size,0,NULL,FNEW);
}

void * operator new[](size_t size) THROW_BADALLOC {
	return memtrace::traced_new(size,0,NULL,FNEWARR);
}

void operator delete(void * p) THROW_NOTHING {
	memtrace::traced_delete(p,FDELETE);
}

void operator delete[](void * p) THROW_NOTHING {
	memtrace::traced_delete(p,FDELETEARR);
}
#if __cplusplus >= 201402L
void operator delete(void * p, size_t) THROW_NOTHING {
	memtrace::traced_delete(p,FDELETE);
}

void operator delete[](void * p, size_t) THROW_NOTHING {
	memtrace::traced_delete(p,FDELETEARR);
}
#endif

/* Visual C++ 2012 miatt kell, mert háklis, hogy nincs megfelelő delete, bár senki sem használja */
void operator delete(void * p, int, const char *) THROW_NOTHING {
	memtrace::traced_delete(p,FDELETE);
}

void operator delete[](void * p, int, const char *) THROW_NOTHING {
	memtrace::traced_delete(p,FDELETE);
}

#endif/*MEMTRACE_CPP*/

/*******************************************************************/
/* initialize */
/*******************************************************************/

START_NAMESPACE
	static void initialize() {
		static BOOL first = TRUE;
		if(first) {
            fperror = stderr;
            random_byte = (unsigned char)time(NULL);
			first = FALSE;
			dying = FALSE;
			#ifdef MEMTRACE_TO_MEMORY
				registry.next = NULL;
				#if !defined(USE_ATEXIT_OBJECT) && defined(MEMTRACE_AUTO)
					atexit((void(*)(void))mem_check);
				#endif
			#endif
			#ifdef MEMTRACE_TO_FILE
				trace_file = fopen("memtrace.dump","w");
			#endif
			#ifdef MEMTRACE_CPP
				_new_handler = NULL;
				delete_called = FALSE;
				delete_call = pack(0,NULL,0,NULL);
			#endif
		}
	}

#if defined(MEMTRACE_TO_MEMORY) && defined(USE_ATEXIT_OBJECT)
    int atexit_class::counter = 0;
    int atexit_class::err = 0;
#endif
END_NAMESPACE
#endif
