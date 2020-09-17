#include <iostream>
#include <string>
#include "Unit.h"

using namespace std;

int main(int argc, char* argv[])
{

	if (argc == 7)
	{
		try
		{
			Unit maple(argv[1], stoi(argv[2]), stoi(argv[3]));
			Unit sally(argv[4], stoi(argv[5]), stoi(argv[6]));

			Unit::Battle(maple, sally);
		}
		catch (const exception& e)
		{
			cerr << "[ERROR]: Program failed to initialise combatants! Make soure the input parameters are valid." << endl;
		}
	}

	return 0;
}


