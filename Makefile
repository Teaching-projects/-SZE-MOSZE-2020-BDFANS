OBJS := Unit.o Hero.o JSON.o Monster.o main.o
CFLAGS := -std=c++17 -Wall -Wextra -Werror
CC := g++-9

cppobj := cppcheck
cppflag := --enable=warning --error-exitcode=1
cppout := --enable=all --output-file=cppcheckartifact.txt

valobj := valgrind
valflag := --track-origins=yes --error-exitcode=1 --leak-check=full

build: $(OBJS)
	$(CC) $(CFLAGS) -o add $(OBJS)

Unit.o: Unit.cpp Unit.h JSON.h
	$(CC) $(CFLAGS) -c Unit.cpp

Hero.o: Hero.cpp Hero.h JSON.h
	$(CC) $(CFLAGS) -c Hero.cpp

JSON.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp

Monster.o: Monster.cpp Monster.h
	$(CC) $(CFLAGS) -c Monster.cpp

main.o: main.cpp Hero.h JSON.h Monster.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -rf *.o add ./docs

doc:
	doxygen doxygenconfig

checkccpout:
	$(cppobj) *.cpp $(cppout)

analysis:
	$(cppobj) *.cpp $(cppflag)


memtest:
	$(valgrind) $(valflag) ./battle scenario2.json