OBJS := Unit.o Hero.o JSON.o Monster.o main.o Map.o Game.o MarkedMap.o PreparedGame.o HeroTextRenderer.o ObserverTextRenderer.o ObserverSVGRenderer.o CharacterSVGRenderer.o
CFLAGS := -std=c++17 -Wall -Wextra -Werror
CC := g++-9

cppobj := cppcheck
cppflag := --enable=warning --error-exitcode=1
cppout := --enable=all --output-file=cppcheckartifact.txt

valobj := valgrind
valflag := --error-exitcode=1 --leak-check=full

build: $(OBJS)
	$(CC) $(CFLAGS) -o battle $(OBJS)

Unit.o: Unit.cpp Unit.h JSON.h Damage.h
	$(CC) $(CFLAGS) -c Unit.cpp

Hero.o: Hero.cpp Hero.h JSON.h Damage.h
	$(CC) $(CFLAGS) -c Hero.cpp

JSON.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp

Monster.o: Monster.cpp Monster.h Damage.h
	$(CC) $(CFLAGS) -c Monster.cpp

Map.o: Map.cpp Map.h
	$(CC) $(CFLAGS) -c Map.cpp

Game.o: Map.h Unit.h Hero.h Monster.h Game.cpp Game.h Renderer.h
	$(CC) $(CFLAGS) -c Game.cpp

MarkedMap.o: MarkedMap.cpp MarkedMap.h
	$(CC) $(CFLAGS) -c MarkedMap.cpp

HeroTextRenderer.o: HeroTextRenderer.cpp HeroTextRenderer.h TextRenderer.h
	$(CC) $(CFLAGS) -c HeroTextRenderer.cpp

ObserverTextRenderer.o: ObserverTextRenderer.cpp ObserverTextRenderer.h TextRenderer.h
	$(CC) $(CFLAGS) -c ObserverTextRenderer.cpp

ObserverSVGRenderer.o: ObserverSVGRenderer.cpp ObserverSVGRenderer.h SVGRenderer.h
	$(CC) $(CFLAGS) -c ObserverSVGRenderer.cpp

CharacterSVGRenderer.o: CharacterSVGRenderer.cpp CharacterSVGRenderer.h SVGRenderer.h
	$(CC) $(CFLAGS) -c CharacterSVGRenderer.cpp

PreparedGame.o: PreparedGame.cpp PreparedGame.h MarkedMap.h JSON.h Game.h
	$(CC) $(CFLAGS) -c PreparedGame.cpp

main.o: main.cpp Hero.h JSON.h Monster.h Damage.h Game.h PreparedGame.h HeroTextRenderer.h ObserverTextRenderer.h ObserverSVGRenderer.h CharacterSVGRenderer.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -rf *.o add ./docs

doc:
	doxygen doxygenconfig

checkcppout:
	$(cppobj) *.cpp $(cppout)

analysis:
	$(cppobj) *.cpp $(cppflag)


memtest:
	$(valgrind) $(valflag) ./battle scenario2.json