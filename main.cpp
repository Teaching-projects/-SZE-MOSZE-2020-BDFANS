#include <iostream>
#include <string>
#include "Unit.h"
#include "Battle.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Unit* a = Unit::praseUnit(argv[1]);
		Unit* b = Unit::praseUnit(argv[2]);
		if (argc < 2) {
			cerr << "Not enough input" << endl;
			return 1;
		}	
		Battle(*a, *b);

		delete a;
		delete b;
	}
	catch (const exception& e)
	{
		cerr << "[ERROR]: Program failed to initialise combatants! Make sure the combatant files provided are valid!" << endl;
		return 1;
	}
	

	return 0;
}


