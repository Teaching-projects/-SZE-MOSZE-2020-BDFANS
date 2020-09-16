# -SZE-MOSZE-2020-BDFANS

A program jelenlegi működéséért a "Unit" nevezetű osztály felel, ami az egymással harcoló NPC megvalósításáért felelős.

Ennek az osztálynak 3 belső változója van:
    string name:Az NPC neve.
	int health: Az NPC életereje.
	int damage: Az NPC alapból mennyi életerőt vesz el támadáskor.

Az osztály létrejöttéért a konstruktornak a bemeneti adatokat "name, health, damage" sorrendben kell megadni. abban az esetben ha valamelyik bemenetre nem adunk értéket(vagy default konstruktort hívás történik) akkor az objektum default értékeket kap.

A harcot a statikus "Battle(Unit& attacker, Unit& defender)" függvényel lehet, ami a következőképpen működik:
    1.  kiírja a harcoló felek adatait.
    2.  Megkezdődik a harc, amely során az "attacker" meghívja az "attack(Unit& target) függvényt a "defender"-re
        Az attack(Unit& target) függvény kivonja a támadó sebzését-t, a "target" életerejéből, vagy ha a sebzés magasabb mint a célpont életereje, akkor azt lenullázza.
        Ezután függvény a csata következményét kiírja.
    3.  Ha a "defendernek" maradt még életereje, akkor ő is meghívja az "attack" függvényt az "attacker"-re
    4.  Ha mindkét félnek maradt még életereje, akkor a függvény a 2. lépéstől megismétlődik.