#include <iostream>

#include "Unit.h"

using namespace std;

int main(int argc, char* argv[])
{
	Unit maple("Maple", 150,	10);
	Unit sally("Sally", 45,		30);


	Unit::Battle(maple, sally);

	return 0;
}


