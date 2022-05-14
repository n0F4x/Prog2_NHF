#ifndef GTEST_LITE_H
#define GTEST_LITE_H

/**
 * \file gtest_lite.h  (v3/2019)
 *
 * Google gtest keretrendszerhez hasonló rendszer.
 * Sz.I. 2015., 2016., 2017. (_Has_X)
 * Sz.I. 2018 (template), ENDM, ENDMsg, nullptr_t
 * Sz.I. 2019 singleton
 * Sz.I. 2021 ASSERT.., STRCASE...
 * Sz.I. 2021 EXPEXT_REGEXP, CREATE_Has_fn_, cmp w. NULL
 *
 * A tesztelés legalapvetőbb funkcióit támogató függvények és makrók.
 * Nem szálbiztos megvalósítás.
 *
 *
 * Szabadon felhasználható, bővíthető.
 *
 * Használati példa:
 *   Teszteljük az f(x)=2*x függvényt:
 * int f(int x) { return 2*x; }
 *
 * int main() {
 *   TEST(TeszEsetNeve, TesztNeve)
 *     EXPECT_EQ(0, f(0));
 *     EXPECT_EQ(4, f(2)) << "A függvény hibás eredményt adott" << std::endl;
 *     ...
 *   END
 * ...
 * // Fatális hiba esetén a teszteset nem fut tovább. Ezek az ASSERT... makrók.
 * // Nem lehet a kiírásukhoz további üzenetet fűzni. PL:
 *   TEST(TeszEsetNeve, TesztNeve)
 *     ASSERT_NO_THROW(f(0));  // itt nem lehet << "duma"
 *     EXPECT_EQ(4, f(2)) << "A függvény hibás eredményt adott" << std::endl;
 *     ...
 *   END
 *  ...
 *
 * A működés részleteinek megértése szorgalmi feladat.
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <cstdlib>
#include <string>
#include <fstream>
#if __cplusplus >= 201103L
# include <iterator>
# include <regex>
#endif
#ifdef MEMTRACE
# include "memtrace.h"
#endif

// Két makró az egyes tesztek elé és mögé:
// A két makró a kapcsos zárójelekkel egy új blokkot hoz létre, amiben
// a nevek lokálisak, így elkerülhető a névütközés.

/// Teszt kezdete. A makró paraméterezése hasonlít a gtest
/// paraméterezéséhez. Így az itt elkészített testek könnyen átemelhetők
/// a gtest keretrendszerbe.
/// @param C - teszteset neve (csak a gtest kompatibilitás miatt van külön neve az eseteknek)
/// @param N - teszt neve
#define TEST(C, N) do { gtest_lite::test.begin(#C"."#N);

/// Teszteset vége.
#define END gtest_lite::test.end(); } while (false);

/// Teszteset vége allokált blokkok számának összehasonlításával
/// Ez az ellenőrzés nem bomba biztos.
#define ENDM gtest_lite::test.end(true); } while (false);

/// Teszteset vége allokált blokkok számának összehasonlításával
/// Ez az ellenőrzés nem bomba biztos.
/// Ha hiba van kiírja az üzenetet.
#define ENDMsg(t) gtest_lite::test.end(true) << t << std::endl; } while (false);

// Eredmények vizsgálatát segítő makrók.
// A paraméterek és a funkciók a gtest keretrendszerrel megegyeznek.

/// Sikeres teszt makrója
#define SUCCEED() gtest_lite::test.expect(true, __FILE__, __LINE__, "SUCCEED()", true)

/// Sikertelen teszt fatális hiba makrója
#define FAIL() gtest_lite::test.expect(false, __FILE__, __LINE__, "FAIL()", true)

/// Sikertelen teszt makrója
#define ADD_FAILURE() gtest_lite::test.expect(false, __FILE__, __LINE__, "ADD_FAILURE()", true)

/// Azonosságot elváró makró
#define EXPECT_EQ(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::eq, __FILE__, __LINE__, "EXPECT_EQ(" #expected ", " #actual ")" )

/// Eltérést elváró makró
#define EXPECT_NE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::ne, __FILE__, __LINE__, "EXPECT_NE(" #expected ", " #actual ")", "etalon" )

/// Kisebb, vagy egyenlő relációt elváró makró
#define EXPECT_LE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::le, __FILE__, __LINE__, "EXPECT_LE(" #expected ", " #actual ")", "etalon" )

/// Kisebb, mint relációt elváró makró
#define EXPECT_LT(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::lt, __FILE__, __LINE__, "EXPECT_LT(" #expected ", " #actual ")", "etalon" )

/// Nagyobb, vagy egyenlő relációt elváró makró
#define EXPECT_GE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::ge, __FILE__, __LINE__, "EXPECT_GE(" #expected ", " #actual ")", "etalon" )

/// Nagyobb, mint relációt elváró makró
#define EXPECT_GT(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::gt, __FILE__, __LINE__, "EXPECT_GT(" #expected ", " #actual ")", "etalon" )

/// Igaz értéket elváró makró
#define EXPECT_TRUE(actual)  gtest_lite::EXPECT_(true, actual,  gtest_lite::eq, __FILE__, __LINE__, "EXPECT_TRUE(" #actual ")" )

/// Hamis értéket elváró makró
#define EXPECT_FALSE(actual) gtest_lite::EXPECT_(false, actual, gtest_lite::eq, __FILE__, __LINE__, "EXPECT_FALSE(" #actual ")" )

/// Valós számok azonosságát elváró makró
#define EXPECT_FLOAT_EQ(expected, actual)  gtest_lite::EXPECT_(expected, actual, gtest_lite::almostEQ, __FILE__, __LINE__, "EXPECT_FLOAT_EQ(" #expected ", " #actual ")" )

/// Valós számok azonosságát elváró makró
#define EXPECT_DOUBLE_EQ(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::almostEQ, __FILE__, __LINE__, "EXPECT_DOUBLE_EQ(" #expected ", " #actual ")" )

/// C stringek (const char *) azonosságát tesztelő makró
#define EXPECT_STREQ(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::eqstr, __FILE__, __LINE__, "EXPECT_STREQ(" #expected ", " #actual ")" )

/// C stringek (const char *) eltéréset tesztelő makró
#define EXPECT_STRNE(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::nestr, __FILE__, __LINE__, "EXPECT_STRNE(" #expected ", " #actual ")", "etalon" )

/// C stringek (const char *) azonosságát tesztelő makró (kisbetű/nagybetű azonos)
#define EXPECT_STRCASEEQ(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::eqstrcase, __FILE__, __LINE__, "EXPECT_STRCASEEQ(" #expected ", " #actual ")" )

/// C stringek (const char *) eltéréset tesztelő makró (kisbetű/nagybetű azonos)
#define EXPECT_STRCASENE(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::nestrcase, __FILE__, __LINE__, "EXPECT_STRCASENE(" #expected ", " #actual ")", "etalon" )

/// Kivételt várunk
#define EXPECT_THROW(statement, exception_type) try { gtest_lite::test.tmp = false; statement; } \
    catch (exception_type) { gtest_lite::test.tmp = true; } \
    catch (...) { } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott '"#exception_type"' kivetelt.")

/// Kivételt várunk
#define EXPECT_ANY_THROW(statement) try { gtest_lite::test.tmp = false; statement; } \
    catch (...) { gtest_lite::test.tmp = true; } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott kivetelt.")

/// Nem várunk kivételt
#define EXPECT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    EXPECTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")

/// Nem várunk kivételt
#define ASSERT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    ASSERTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")

/// Kivételt várunk és továbbdobjuk -- ilyen nincs a gtest-ben
#define EXPECT_THROW_THROW(statement, exception_type) try { gtest_lite::test.tmp = false; statement; } \
    catch (exception_type) { gtest_lite::test.tmp = true; throw; } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott '"#exception_type"' kivetelt.")

/// Környezeti változóhoz hasonlít -- ilyen nincs a gtest-ben
#define EXPECT_ENVEQ(expected, actual) gtest_lite::EXPECTSTR(std::getenv(expected), actual, gtest_lite::eqstr, __FILE__, __LINE__, "EXPECT_ENVEQ(" #expected ", " #actual ")" )

/// Környezeti változóhoz hasonlít -- ilyen nincs a gtest-ben (kisbetű/nagybetű azonos)
#define EXPECT_ENVCASEEQ(expected, actual) gtest_lite::EXPECTSTR(std::getenv(expected), actual, gtest_lite::eqstrcase, __FILE__, __LINE__, "EXPECT_ENVCASEEQ(" #expected ", " #actual ")" )

#if __cplusplus >= 201103L
/// Reguláris kifejezés illesztése
# define EXPECT_REGEXP(expected, actual, match, err) gtest_lite::EXPECTREGEXP(expected, actual, match, err, __FILE__, __LINE__, "EXPECT_REGEXP(" #expected ", " #actual ", " #match ")" )
#endif
////--------------------------------------------------------------------------------------------
/// ASSERT típusú ellenőrzések. CSak 1-2 van megvalósítva. Nem ostream& -val térnek vissza !!!
/// Kivételt várunk

/// Azonosságot elváró makró
#define ASSERT_EQ(expected, actual) gtest_lite::ASSERT_(expected, actual, gtest_lite::eq, "ASSER_EQ")

/// Nem várunk kivételt
#define ASSERT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    ASSERTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")


/// Segédmakró egy adattag, vagy tagfüggvény létezésének tesztelésére futási időben
/// Ötlet:
/// https://cpptalk.wordpress.com/2009/09/12/substitution-failure-is-not-an-error-2
/// Használat:
/// CREATE_Has_(size)
/// ... if (_Has_size<std::string>::member)...
#define CREATE_Has_(X) \
template<typename T> struct _Has_##X {  \
    struct Fallback { int X; };         \
    struct Derived : T, Fallback {};    \
    template<typename C, C> struct ChT; \
    template<typename D> static char (&f(ChT<int Fallback::*, &D::X>*))[1]; \
    template<typename D> static char (&f(...))[2]; \
    static bool const member = sizeof(f<Derived>(0)) == 2; \
};

#define CREATE_Has_fn_(X, S) \
template<typename R, typename T> struct _Has_fn_##X##_##S {  \
    template<typename C, R (C::*f)() S> struct ChT; \
    template<typename D> static char (&f(ChT<D, &D::X>*))[1]; \
    template<typename D> static char (&f(...))[2]; \
    static bool const fn = sizeof(f<T>(0)) == 1; \
};

/// Segédfüggvény egy publikus adattag, vagy tagfüggvény létezésének tesztelésére
/// fordítási időben
inline void hasMember(...) {}

/// Segédsablon típuskonverzió futás közbeni ellenőrzésere
template <typename F, typename T>
struct _Is_Types {
    template<typename D> static char (&f(D))[1];
    template<typename D> static char (&f(...))[2];
    static bool const convertable = sizeof(f<T>(F())) == 1;
};

/// -----------------------------------
/// Belső megvalósításhoz tartozó makrók, és osztályok.
/// Nem célszerű közvetlenül használni, vagy módosítani
/// -----------------------------------

/// EXPECTTHROW: kivételkezelés
#define EXPECTTHROW(statement, exp, act) gtest_lite::test.expect(gtest_lite::test.tmp, __FILE__, __LINE__, #statement) \
    << "** Az utasitas " << (act) \
    << "\n** Azt vartuk, hogy " << (exp) << std::endl

#define ASSERTTHROW(statement, exp, act) gtest_lite::test.expect(gtest_lite::test.tmp, __FILE__, __LINE__, #statement) \
    << "** Az utasitas " << (act) \
    << "\n** Azt vartuk, hogy " << (exp) << std::endl; if (!gtest_lite::test.status) { gtest_lite::test.end(); break; }

#define ASSERT_(expected, actual, fn, op) EXPECT_(expected, actual, fn, __FILE__, __LINE__, #op "(" #expected ", " #actual ")" ); \
    if (!gtest_lite::test.status) { gtest_lite::test.end(); break; }

#ifdef CPORTA
#define GTINIT(is)  \
    int magic;      \
    is >> magic;
#else
#define GTINIT(IS)
#endif // CPORTA

#ifdef CPORTA
#define GTEND(os)  \
    os << magic << (gtest_lite::test.fail() ? " NO" : " OK?") << std::endl;
#else
#define GTEND(os)
#endif // CPORTA

/// gtest_lite: a keretrendszer függvényinek és objektumainak névtere
namespace gtest_lite {

/// Tesztek állapotát tároló osztály.
/// Egyetlen egy statikus példány keletkezik, aminek a
/// destruktora a futás végén hívódik meg.
struct Test {
    int sum;            ///< tesztek számlálója
    int failed;         ///< hibás tesztek
    int ablocks;        ///< allokált blokkok száma
    bool status;        ///< éppen futó teszt státusza
    bool tmp;           ///< temp a kivételkezeléshez;
    std::string name;   ///< éppen futó teszt neve
    std::fstream null;  ///< nyelő, ha nem kell kiírni semmit
    std::ostream& os;   ///< ide írunk
    static Test& getTest() {
        static Test instance;///< egyedüli (singleton) példány
        return instance;
    }
private:    /// singleton minta miatt
    Test() :sum(0), failed(0), status(false), null("/dev/null"), os(std::cout) {}
    Test(const Test&);
    void operator=(const Test&);
public:
    /// Teszt kezdete
    void begin(const char *n) {
        name = n; status = true;
#ifdef MEMTRACE
        ablocks = memtrace::allocated_blocks();
#endif
        os << "\n---> " << name << std::endl;
        ++sum;
    }
    /// Teszt vége
    std::ostream& end(bool memchk = false) {
#ifdef MEMTRACE
        if (memchk && ablocks != memtrace::allocated_blocks()) {
            status = false;
            return os << "** Lehet, hogy nem szabaditott fel minden memoriat! **" << std::endl;
        }
#endif
        os << (status ? "     SIKERES" : "** HIBAS ****") << "\t" << name << " <---" << std::endl;
#ifdef CPORTA
        if (!status)
            std::cerr << (status ? "     SIKERES" : "** HIBAS ****") << "\t" << name << " <---" << std::endl;
#endif // CPORTA
        if (!status)
            return os;
        else
            return null;
    }

    bool fail() { return failed; }

    bool astatus() { return status; }

    /// Eredményt adminisztráló tagfüggvény True a jó eset.
    std::ostream& expect(bool st, const char *file, int line, const char *expr, bool pr = false) {
        if (!st) {
            ++failed;
            status = false;
        }
        if (!st || pr) {
            std::string str(file);
            size_t i = str.rfind("\\");
            if (i == std::string::npos) i = str.rfind("/");
            if (i == std::string::npos) i = 0; else i++;
            return os << "\n**** " << &file[i] << "(" << line << "): " << expr << " ****" << std::endl;
        }
        return null;
    }

    /// Destruktor
    ~Test() {
        if (sum != 0) {
            os << "\n==== TESZT VEGE ==== HIBAS/OSSZES: " << failed << "/" << sum << std::endl;
#ifdef CPORTA
            if (failed)
                std::cerr << "\n==== TESZT VEGE ==== HIBAS/OSSZES: " << failed << "/" << sum << std::endl;
#endif // CPORTA
        }
    }
};

/// A statikus referencia minden fordítási egységben keletkezik, de
/// mindegyik egyetlen példányra fog hivatkozni a singleton minta miatt
static Test& test = Test::getTest();

/// általános sablon a várt értékhez.
template <typename T>
std::ostream& EXPECT_(T exp, T act, bool (*pred)(T, T), const char *file, int line,
                      const char *expr, const char *lhs = "elvart", const char *rhs = "aktual") {
    return test.expect(pred(exp, act), file, line, expr)
        << "** " << lhs << ": " << std::boolalpha << exp
        << "\n** " << rhs << ": " << std::boolalpha << act << std::endl;
}

/// pointerre specializált sablon a várt értékhez.
template <typename T>
std::ostream& EXPECT_(T* exp, T* act, bool (*pred)(T*, T*), const char *file, int line,
                      const char *expr, const char *lhs = "elvart", const char *rhs = "aktual") {
    return test.expect(pred(exp, act), file, line, expr)
        << "** " << lhs << ": " << (void*) exp
        << "\n** " << rhs << ": " << (void*) act << std::endl;
}

#if __cplusplus >= 201103L
/// nullptr-re specializált sablon a várt értékhez.
template <typename T>
std::ostream& EXPECT_(std::nullptr_t exp, T* act, bool (*pred)(T*, T*), const char *file, int line,
                      const char *expr, const char *lhs = "elvart", const char *rhs = "aktual") {
    return test.expect(pred(exp, act), file, line, expr)
        << "** " << lhs << ": " << (void*) exp
        << "\n** " << rhs << ": " << (void*) act << std::endl;
}

template <typename T>
std::ostream& EXPECT_(T* exp, std::nullptr_t act, bool (*pred)(T*, T*), const char *file, int line,
                      const char *expr, const char *lhs = "elvart", const char *rhs = "aktual") {
    return test.expect(pred(exp, act), file, line, expr)
        << "** " << lhs << ": " << (void*) exp
        << "\n** " << rhs << ": " << (void*) act << std::endl;
}
#endif

/// stringek összehasonlításához.
/// azért nem spec. mert a sima EQ-ra másként kell működnie.
inline
std::ostream& EXPECTSTR(const char *exp, const char *act, bool (*pred)(const char*, const char*), const char *file, int line,
                      const char *expr, const char *lhs = "elvart", const char *rhs = "aktual") {
    return test.expect(pred(exp, act), file, line, expr)
        << "** " << lhs << ": " << (exp == NULL ? "NULL pointer" : std::string("\"") + exp + std::string("\""))
        << "\n** " << rhs << ": " << (act == NULL ? "NULL pointer" : std::string("\"") + act + std::string("\"")) << std::endl;
}

#if __cplusplus >= 201103L
/// regexp összehasonlításhoz.
template <typename E, typename S>
int count_regexp(E exp, S str) {
    std::regex rexp(exp);
    auto w_beg = std::sregex_iterator(str.begin(), str.end(), rexp);
    auto w_end = std::sregex_iterator();
    return std::distance(w_beg, w_end);
}

template <typename E, typename S>
std::ostream& EXPECTREGEXP(E exp, S str, int match, const char *err,  const char *file, int line,
                    const char *expr, const char *lhs = "regexp", const char *rhs = "string",
                    const char *m = "elvart/illeszkedik") {
    int cnt = count_regexp(exp, str);
    if (match < 0) match = cnt;
    return test.expect(cnt == match, file, line, expr)
        << "** " << lhs << ": " << std::string("\"") + exp + std::string("\"")
        << "\n** " << rhs << ": " << (err == NULL ? std::string("\"") + str + std::string("\"") : err)
        << "\n** " << m << ": " << match << "/" << cnt << std::endl;
}
#endif

/// segéd sablonok a relációkhoz.
/// azért nem STL (algorithm), mert csak a függvény lehet, hogy menjen a deduckció
template <typename T>
bool eq(T a, T b) { return a == b; }

inline
bool eqstr(const char *a, const char *b) {
    if (a != NULL && b != NULL)
        return strcmp(a, b) == 0;
    return false;
}

inline
bool eqstrcase(const char *a, const char *b) {
    if (a != NULL && b != NULL) {
        while (toupper(*a) == toupper(*b) && *a != '\0') {
            a++;
            b++;
        }
        return *a == *b;
    }
    return false;

}

template <typename T>
bool ne(T a, T b) { return a != b; }

inline
bool nestr(const char *a, const char *b) {
    if (a != NULL && b != NULL)
        return strcmp(a, b) != 0;
    return false;
}

template <typename T>
bool le(T a, T b) { return a <= b; }

template <typename T>
bool lt(T a, T b) { return a < b; }

template <typename T>
bool ge(T a, T b) { return a >= b; }

template <typename T>
bool gt(T a, T b) { return a > b; }

/// Segédsablon valós számok összehasonlításához
/// Nem bombabiztos, de nekünk most jó lesz
/// Elméleti hátér:
/// http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
template <typename T>
bool almostEQ(T a, T  b) {
    // eps: ha a relatív, vagy abszolút hiba ettől kisebb, akkor elfogadjuk
    T eps = 10 * std::numeric_limits<T>::epsilon(); // 10-szer a legkisebb érték
    if (a == b) return true;
    if (fabs(a - b) < eps)
       return true;
    double aa = fabs(a);
    double ba = fabs(b);
    if (aa < ba) {
        aa = ba;
        ba = fabs(a);
    }
    return (aa - ba) < aa * eps;
}

/// Segédsablon ostream átirányításához
/// A destruktor visszaállít
class ostreamRedir {
    std::ostream& src;
    std::streambuf *const save;
public:
    ostreamRedir(std::ostream& src, std::ostream& dst)
            : src(src), save(src.rdbuf(dst.rdbuf())) {}
    ~ostreamRedir() { src.rdbuf(save); }
};

} // namespace gtest_lite

#endif // GTEST_LITE_H
