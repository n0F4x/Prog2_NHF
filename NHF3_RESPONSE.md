Első élményem:
Hibátlanul fordul, minden tök király. Futtatom. Várok. Még mindig várok... Kilövöm a programot, mert azt hiszem végtelen ciklusba került. Nekiállok debuggolni, megnézem a main-t. Ja, hogy itt egy inputra vár! Csodás...

Amúgy viccet félretéve valami kiírás nem ártott volna. Még jobb lenne, ha magától lefutna az összes teszt és kiírná mindegyikhez, hogy sikerült (vagy azt, hogy nem).

A tesztek írásához egy kis segítség. Először nem kell ilyen nagy átfogó tesztet írni, mint, hogy `App.run()`. Kezdhetsz mondjuk azzal, hogy a saját vector-odhoz írsz teszteket. Létrehozod. Pelepakolsz egy elemet. Lekérdezed, hogy mennyi a mérete. Teszteled, hogy az iterátorok jól működnek-e. Meg ehhez hasonlók.

Feleslegesen sok időt szántam rá, de végigrágram magamat mindenen.

- Angle
  - Látom, eltűnt az osztály.
  - Ez egyáltalán nem baj, teljesen jó az is, ha csak függvények vannak.
  - Azt viszont nem értem, hogy miért van `long double` meg `unsigned long long` paraméterük ha úgyis float-ra kasztolod őket.
  - Én inkább úgy csinálnám, hogy float-ot veszek át és majd kasztolgat az aki meg akarja hívni a függvényeket.
- App
  - Ez így van.
- AppData
  - Egyelőre nagyon úgy néz ki nekem, hogy nem csinál semmit sem.
  - Úgyhogy ha a jövőben sem tervezed használni, akkor kérlek töröljed ki.
- BezierEasing.
  - Mondtad, hogy másoltad, meg a forráskódban is szépen megjelölted.
  - Másét viszont nem fogom javítani.
- Controller
  - Eléggé kontrasztos, hogy egymás alatti sorokban látok smart és raw pointereket.
  - Szebb lenne, hogyha a raw pointer helyett is smart pointert használnál.
  - Mondjuk nem mintha ez Prog2-ből elvárás lenne.
  - Úgyhogy ajánlom figylemedbe az alábbi cikkeket. Különösen az utolsót.
    - [std::unique_ptr](https://www.learncpp.com/cpp-tutorial/stdunique_ptr/)
    - [std::shared_ptr](https://www.learncpp.com/cpp-tutorial/stdshared_ptr/)
    - [std::weak_ptr](https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/)
- GameMenu
  - Ez így van. :D
- InitMenu
  - Nagyon nagyon üres.
  - Láttam már, hogy máshol használod.
  - De biztos szükség van erre az oszályra és nem lehetne használni helyette az ősosztályát?
- main.cpp
  - Ide tartozik az első élményem a tesztekkel.
- MainMenu
  - A Menu::open függvényt hívod.
  - Miért???
  - Az open függvény a MenuBase-ben van definiálva.
  - Persze, működik, mert emiatt a Menu-nek is van open függvénye...
  - De na. Ha csak simán azt írod, hogy open, akkor az is működne, mert sehol sem volt felülírva.
- Math
  - A square függvénynél én a visszatérési értéket mindenképpen meghagynám T-nek.
  - Majd ha a használónak mindenképpen float kell eredményként, akkor kasztol ő.
- Menu
  - Jól néz ki.
- MenuBase
  - Mondjuk nem értem még teljesen, hogy mire használod, hogy van MenuBase és Menu is.
- MenuItem
  - Itt is raw pointer van használva.
- MenuNode
  - Az addChild függvény nagyon túl van bonyolítva. Gondolkod el rajta miért! Ha nem lett meg laborig, akkor kérdezz rá!
  - Illene a függvényeket a cpp-ben megírni. Különösképpen a findChild-ot.
  - Meg amúgy nem std::unique_ptr-t kéne használni, hanem std::shared_ptr-t és akkor nem kéne kibányászni a raw pointert és azt visszaadni, mert az nagyon nem szép így ahogy most van.
  - OptionsMenu:
    - Menu::close()...
  - Platform
    - A getWidth függvény lehetne statukus.
    - Mármint igazából szükség sincsen rá, mert publikus a width.
    - Bevallom a matekot nem ellenőriztem le mögötte. Ha működött, akkor remélem minden rendben van vele.
  - PlatformContainer
    - Az update föggvényben amikor az első elemre hívod, a rotate függvényt, akkor annak a paraméterét szebb lenne kivenni külön változóba, hogy olvashatóbb legyen a kód.
  - Player
    - Úgy érzem még nincsen kész, meg ami kész volt, azt is kiszedted a JPorta miatt.
    - De azért örülök, hogy ez is készülőben van.
  - PolarVector
    - Ha tényleg csak ennyi lesz az osztály, akkor legyen inkább struct és akkor nem kell kiírni, hogy public.
  - PreCalculator
    - Már láttam korábban, hogy használod ezt az osztályt.
    - De még nem fejtettem meg, hogy mit csinál ponoan.
    - Majd laboron kiszedem belőled. :D
  - Track
    - Érdekes, hogy ő is egy MenuItem.
    - Majd ezrről is beszéljünk, mert érdekel.
  - Transitionable
    - Adom a nevét.
  - Transitions
    - Szúrja a szememet, hogy a hpp-ben deklarálod a Transitionable osztály.
    - Miért nem húzod be csak a headert hozzá?
    - Ha majd kijavítod, akkor figylej rá, hogy a cpp-ben már nem kell majd behúznod.
  - Vector
    - Vectoron belül _vector-nak hívni az adatokra mutató pointert elég erős.
    - Hogyhogy nem data vagy valami hasonló?
  - Window
    - R.I.P
  
  Egyelőre ennyi. :D Majd úgy is beszélünk még.
  