# Annak felüljavítaná a javításomat

Mivel Gábor C++20-at használ és emiatt úgysem fordul a kódja, ezért abban egyeztünk meg vele, hogy git-en keresztül is eljuttathatja hozzám a feladatát, az alábbi kikötésekkel:
- Azt a commit-ot ahol szeretné, hogy értékeljem a háziját meg kell jelölnie egy tag-gel, vagy egy külön branch-el.
- Ez a commit még a beadási határidő előtt kell, hogy legyen.
- A repoitory-hoz elérhető kell legyen a számomra.

Ez mind meg is történt [itt](https://github.com/n0F4x/Prog2_NHF/tree/NHF4_Final).

# Gábornak

## Csak úgy ami az elején eszembe jutott

Beadtál nekem 128 oldal dokumentációt... Te jó ég! Azért ugye nem haragszol meg, hogy nem olvasom végig?

Amúgy viccet félretéve nagyon király, hogy ennyit foglalkoztál vele, de azért elég sok felesleges dolog is került bele. Például a headerek kódját a végén egyáltalán nem érzem szükségesnek.

A CMakeLists.txt-ből hiányzott pár file, de nem baj, simán megoldódott.

Ha a teszteket memtrace helyett address sanitizer-rel futtattam, akkor minden tökéletesen működött.

## A konkrét fájlfaidhoz

- Context
  - A string függvényt én máshogy csináltam volna. Majd megbeszéljük szóban ha érdekel.
- ContextManager
  - Van pár függvény, ami csak úgy a levegőben lóg. Ezekből lehetnének az osztályhoz tartozó privát statikus függvények.
- AppData
  - Az összes függvénynek statikusnak kéne lennie.
- Controller
  - Az isActive függvénynek lehetne beszédesebb neve.
- Window
  - Az aktív várakozás a lockFPS függvényben nem egy olyan szép megoldás.
- Theme
  - Én inkább Colors-nak hívnám. A theme egy jó ötlet, de én a Theme-eket pakolnám össze a Colors felhasználásával.
- Transitionable
  - Hiányzik a `#include <SFML/Graphics.hpp>`.
- Player
  - Az _offset lehetne statikus is.
- PreCalculator
  - A (point - origin) értékét ki lehetne menteni egy lokális változóba, hogy ne legyen ötször is kiszámolva.
- Track
  - A _preCalc attribútum lehetne static const.
- MainMenu
  - Itt is használhatnál smart pointereket a _track és a _player változókhoz.
- Menu
  - Ahhoz, hogy az előző működjön itt az _items-nek shared_ptr-eket kell, hogy tartalmazzon.
- Transition
  - A start függvényt inkább a cpp-ben kéne megírni.
- Math
  - A squaref függvény felesleges, a sima square ugyanazt tudja.