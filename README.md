# -SZE-MOSZE-2020-BDFANS

A program egy egyszerű RPG játékot valósít amely során egy hőst elhelyezünk egy 2 dimentiós térképen különböző szörnyekkel és a cél a hős segítségével az összes szörny megölése. A hős támadás során tapasztalati pontokat szerez, amikből ha elég gyűlik össze, akkor a hős szintet lét és a statisztikási javulnak.

A program egy bemeneti paramétert vár, ami egy olyan szövegfájlnak a neve, ami követi a JSON stílus szabályait és a következő változókat tartalmazza:

  - "map": string - A térkép adatait tartalmazó fájl
  - "hero": string - A hős adatait tartalmazó JSON fájl
  - "monster-[X]" : string, ahol X 1-től 9-ig számok - A különböző szörnyek adatait tartalmazó JSON fájl
  - "wall_texture" : string - A falak terek textúráját tartalmazó SVG fájl
  - "free_texture" : string - Az üres terek textúráját tartalmazó SVG fájl

A program elindítása után, legenerálja a térképet ami után elkezdődik a játék. Ekkor megjlenik a hős által belátható térkép, ami után a program irányjelző bemeneteket fog várni: north:fel south:le east:jobbra west: balra

Ha a hős egy olyan kockára lép ahol szörnyek találhatók, akkor elkezd azokkal harcolni egészen addig amig ő, vagy a  szörnyek mind elesnek. Ha a hőr győzedelmeskedik akkor a játék folytatódik egészen addig amiíg vagy a hős, vagy az összes szörny a térképen elesik.

# JSON és térkép paraméterek

A program sikeres lefutása során szügség van egy térkép fájlra, és több különböző JSON fájltra is szügség van melyeknek a következő változókkal kell rendelkezniük:

"map": A térké a következő stílusu szövegfájlban van megadva

\#\#\#\#\#\#

\# H 1\#

\#2 3\#\#

\#\#\#\#

Ahol a \# karakter a falakat, a H a hőst, a számok a különböző szörnyeket, az üres területek pedig a bejárható tereket jelölik

"hero.json": A hős adatait tartalmazó JSON fájl a következő változókkal kell ellátni:

  - "name": "Prince Aidan of Khanduras" - A hős neve
  - "base_health_points": 30 - A hős életereje
  - "damage": 3 - A hős fizikus sebzése (A célpont védelme befolyásolja)
  - "magical-damage": 2 - A hős mágikus sebzése (A célpont védelme nem befolyásolja)
  - "defense": 1 - A hős páncél ponjai ami csökkenti a beérkező fizikai támadásokat (1 defense 1 damaget von le max 0-ig)
  - "defense_bonus_per_level": 1 - Szintlépésenként szerzett páncél pontok
  - "base_attack_cooldown": 1.1 - a hős támadási sebessége, azaz mennyi időt kell várni két támadás között
  - "experience_per_level": 20 - Mennyi tapasztalati pont kell a szintlépéshez
  - "health_point_bonus_per_level": 5 - Szintlépésenként szerzett életerő
  - "physical_damage_bonus_per_level": 1 - Szintlépésenként szerzett fizikai támadás
  - "magical_damage_bonus_per_level": 1 - Szintlépésenként szerzett mágikus támadás
  - "cooldown_multiplier_per_level": 0.9 - Szintlépésenként növekvő támadási sebesség (ez az érték összeszorzódik a base_attack_cooldown-al)
  - "light_radius": 2 - A hős látótávolsága, azaz a hős hány kocka távolra lát el
  - "light_radius_bonus_per_level": 1 - Szintlépésenként szerzett látótávolság
  - "texture": "Dark_Wanderer.svg" - A hős textúráját tároló SVG fájl neve

"monster-[X].json" A szörnyek adatait hasonló módon JSON fájlokban tároljuk, amelyek a következő, a heroban is megtalálható változókat tárolják:

  - "name": "Fallen" - A szörny neve
  - "base_health_points": 10 - A szörny életereje
  - "damage": 3 - A szörny fizikai sebzése
  - "magical-damage": 2 - A szörny mágikus sebzése
  - "defense": 1 - A szörny páncél pontjai
  - "base_attack_cooldown": 1.1 - A szörny támadási sebessége
  - "texture": "Fallen.svg" - A szörny textúráját tároló SVG fájl neve

# Rendererelők

A program a futása során több különböző módon is kiiratja a játék jelenlegi állásat. Ezek a következők:

    1. standard kimenetre szöveges formátumban azt amit a hős lát.
    2. A log.txt fájlba szöveges formátumban a játék kezdetétől annak összes állapotát.
    3. A pretty.svg fájlba SVG formátumban azt amit a hős lát.
    4. A gamemaster.svg fájlba SVG formátumban a játék jelenlegi állásat

# Dokumentáció

A program dokumentációja az alábbi linken található:
    https://teaching-projects.github.io/-SZE-MOSZE-2020-BDFANS
