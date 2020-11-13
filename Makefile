OBJS := Unit.o Hero.o JSON.o Monster.o main.o
CFLAGS := -std=c++17 -Wall -Wextra -Werror -c
CC := g++-9

cppobj := cppcheck
cppflag := --enable=warning --error-exitcode=1
cppout := --enable=all --output-file=cppcheckartifact.txt

valobj := valgrind
valflag := --track-origins=yes --error-exitcode=1 --leak-check=full

build: $(OBJS)
	$(CC) -Wall -Wextra -o add $(OBJS)

Unit.o: Unit.cpp Unit.h JSON.h
	$(CC) $(CFLAGS) Unit.cpp

Hero.o: Hero.cpp Hero.h JSON.h
	$(CC) $(CFLAGS) Hero.cpp

JSON.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) JSON.cpp

Monster.o: Monster.cpp Monster.h
	$(CC) $(CFLAGS) Monster.cpp

main.o: main.cpp Hero.h JSON.h Monster.h
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o add ./docs

doc:
	doxygen doxygenconfig

checkcpp:
	$(cppobj) *.cpp $(cppout)
	$(cppopj) *.cpp $(cppflag)

memtest:
	$(valgrind) $(valflag) ./battle scenario2.json