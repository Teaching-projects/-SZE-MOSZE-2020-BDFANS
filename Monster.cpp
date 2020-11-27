#include "Monster.h"
#include "JSON.h"

Monster Monster::parse(std::string filename)
{
    JSON data = JSON::parseFromFile(filename);
		std::string innev = "default";
		Damage indmg;
		int inhp = 1;
		indmg.physical = 0;
		indmg.magical = 0;
		int indef = 1;
		double inaspeed = 1.0;
		try
		{
		innev = data.get<std::string>("name");
		inhp = data.get<int>("health_points");
		if (data.get<int>("damage")) {
			indmg.physical = data.get<int>("damage");
		}
		if (data.get<int>("magical-damage")) {
			indmg.magical = data.get<int>("magical-damage");
		}
		inaspeed = data.get<double>("attack_cooldown");

		}
		catch(const std::exception& e)
		{
			std::cerr << "[ERROR] Missing value from input data! Make sure the JSON input data is valid!\n";
		}
		
    return Monster(innev,inhp,indmg,indef,inaspeed);
}