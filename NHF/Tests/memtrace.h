/*********************************
Memoriaszivargas-detektor
Keszitette: Peregi Tamas, BME IIT, 2011
            petamas@iit.bme.hu
Kanari:     Szeberenyi Imre, 2013.,
VS 2012:    Szeberényi Imre, 2015.,
mem_dump:   2016.
inclue-ok:  2017., 2018., 2019., 2021.
*********************************/

#ifndef MEMTRACE_H
#define MEMTRACE_H

#if defined(MEMTRACE)

/*ha definiálva van, akkor a hibakat ebbe a fajlba írja, egyébkent stderr-re*/
/*#define MEMTRACE_ERRFILE MEMTRACE.ERR*/

/*ha definialva van, akkor futas kozben lancolt listat epit. Javasolt a hasznalata*/
#define MEMTRACE_TO_MEMORY

/*ha definialva van, akkor futas kozben fajlba irja a foglalasokat*/
/*ekkor nincs ellenorzes, csak naplozas*/
/*#define MEMTRACE_TO_FILE*/

/*ha definialva van, akkor a megallaskor automatikus riport keszul */
#define MEMTRACE_AUTO

/*ha definialva van, akkor malloc()/calloc()/realloc()/free() kovetve lesz*/
#define MEMTRACE_C

#ifdef MEMTRACE_C
	/*ha definialva van, akkor free(NULL) nem okoz hibat*/
	#define ALLOW_FREE_NULL
#endif

#ifdef __cplusplus
	/*ha definialva van, akkor new/delete/new[]/delete[] kovetve lesz*/
	#define MEMTRACE_CPP
#endif

#if defined(__cplusplus) && defined(MEMTRACE_TO_MEMORY)
	/*ha definialva van, akkor atexit helyett objektumot hasznal*/
	/*ajanlott bekapcsolni*/
	#define USE_ATEXIT_OBJECT
#endif

/******************************************/
/* INNEN NE MODOSITSD                     */
/******************************************/
#ifdef NO_MEMTRACE_TO_FILE
	#undef MEMTRACE_TO_FILE
#endif

#ifdef NO_MEMTRACE_TO_MEMORY
	#undef MEMTRACE_TO_MEMORY
#endif

#ifndef MEMTRACE_AUTO
    #undef USE_ATEXIT_OBJECT
#endif

#ifdef __cplusplus
	#define START_NAMESPACE namespace memtrace {
	#define END_NAMESPACE } /*namespace*/
	#define TRACEC(func) memtrace::func
	#include <new>
#else
	#define START_NAMESPACE
	#define END_NAMESPACE
	#define TRACEC(func) func
#endif

// THROW deklaráció változatai
#if defined(_MSC_VER)
  // VS rosszul kezeli az __cplusplus makrot
  #if _MSC_VER < 1900
    // * nem biztos, hogy jó így *
	#define THROW_BADALLOC
	#define THROW_NOTHING
  #else
    // C++11 vagy újabb
	#define THROW_BADALLOC noexcept(false)
	#define THROW_NOTHING noexcept
  #endif
#else
  #if __cplusplus < 201103L
	// C++2003 vagy régebbi
	#define THROW_BADALLOC throw (std::bad_alloc)
	#define THROW_NOTHING throw ()
  #else
    // C++11 vagy újabb
	#define THROW_BADALLOC noexcept(false)
	#define THROW_NOTHING noexcept
  #endif
#endif

START_NAMESPACE
	int allocated_blocks();
END_NAMESPACE

#if defined(MEMTRACE_TO_MEMORY)
START_NAMESPACE
    int mem_check(void);
    int poi_check(void*);
END_NAMESPACE
#endif

#if defined(MEMTRACE_TO_MEMORY) && defined(USE_ATEXIT_OBJECT)
#include <cstdio>
START_NAMESPACE
	class atexit_class {
		private:
			static int counter;
			static int err;
		public:
			atexit_class() {
#if defined(CPORTA) && !defined(CPORTA_NOSETBUF)
			    if (counter == 0) {
                        setbuf(stdout, 0);
                        setbuf(stderr, 0);
			    }
#endif
			counter++;
			}

			int check() {
				if(--counter == 0)
					err = mem_check();
                return err;
			}

			~atexit_class() {
			    check();
            }
	};

static atexit_class atexit_obj;

END_NAMESPACE
#endif/*MEMTRACE_TO_MEMORY && USE_ATEXIT_OBJECT*/

/*Innentol csak a "normal" include eseten kell, kulonben osszezavarja a mukodest*/
#ifndef FROM_MEMTRACE_CPP
#include <stdlib.h>
#ifdef __cplusplus
	#include <iostream>
/* ide gyűjtjük a nemtrace-vel összeakadó headereket, hogy előbb legyenek */

	#include <fstream>  // VS 2013 headerjében van deleted definició
	#include <sstream>
	#include <vector>
	#include <list>
	#include <map>
	#include <algorithm>
	#include <functional>
	#include <memory>
	#include <iomanip>
	#include <locale>
	#include <typeinfo>
	#include <ostream>
	#include <stdexcept>
	#include <ctime>
    #if __cplusplus >= 201103L
        #include <iterator>
        #include <regex>
    #endif
#endif
#ifdef MEMTRACE_CPP
	namespace std {
		typedef void (*new_handler)();
}
#endif

#ifdef MEMTRACE_C
START_NAMESPACE
	#undef malloc
	#define malloc(size) TRACEC(traced_malloc)(size,#size,__LINE__,__FILE__)
	void * traced_malloc(size_t size, const char *size_txt, int line, const char * file);

	#undef calloc
	#define calloc(count,size) TRACEC(traced_calloc)(count, size, #count","#size,__LINE__,__FILE__)
	void * traced_calloc(size_t count, size_t size, const char *size_txt, int line, const char * file);

	#undef free
	#define free(p) TRACEC(traced_free)(p, #p,__LINE__,__FILE__)
	void traced_free(void * p, const char *size_txt, int line, const char * file);

	#undef realloc
	#define realloc(old,size) TRACEC(traced_realloc)(old,size,#size,__LINE__,__FILE__)
	void * traced_realloc(void * old, size_t size, const char *size_txt, int line, const char * file);

	void mem_dump(void const *mem, size_t size, FILE* fp = stdout);

END_NAMESPACE
#endif/*MEMTRACE_C*/

#ifdef MEMTRACE_CPP
START_NAMESPACE
	#undef set_new_handler
	#define set_new_handler(f) TRACEC(_set_new_handler)(f)
	void _set_new_handler(std::new_handler h);

	void set_delete_call(int line, const char * file);
END_NAMESPACE

void * operator new(size_t size, int line, const char * file) THROW_BADALLOC;
void * operator new[](size_t size, int line, const char * file) THROW_BADALLOC;
void * operator new(size_t size) THROW_BADALLOC;
void * operator new[](size_t size) THROW_BADALLOC;
void operator delete(void * p)  THROW_NOTHING;
void operator delete[](void * p) THROW_NOTHING;

#if __cplusplus >= 201402L
// sized delete miatt: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3536.html
void operator delete(void * p, size_t)  THROW_NOTHING;
void operator delete[](void * p, size_t) THROW_NOTHING;
#endif

/* Visual C++ 2012 miatt kell, mert háklis, hogy nincs megfelelő delete, bár senki sem használja */
void operator delete(void *p, int, const char *) THROW_NOTHING;
void operator delete[](void *p, int, const char *) THROW_NOTHING;


#define new new(__LINE__, __FILE__)
#define delete memtrace::set_delete_call(__LINE__, __FILE__),delete

#ifdef CPORTA
#define system(...)  // system(__VA_ARGS__)
#endif

#endif /*MEMTRACE_CPP*/

#endif /*FROM_MEMTRACE_CPP*/
#else
#pragma message ( "MEMTRACE NOT DEFINED" )
#endif /*MEMTRACE*/

#endif /*MEMTRACE_H*/
