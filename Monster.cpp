#include "Monster.h"
#include "JSON.h"

Monster Monster::parse(std::string filename)
{
    JSON data = JSON::parseFromFile(filename);
		std::string innev = "default";
		int inhp = 1;
		int indef = 1;
		int inphys = 0;
		int inmagic = 0;
		double inaspeed = 1.0;
		try
		{
		innev = data.get<std::string>("name");
		inhp = data.get<int>("health_points");
		if (data.get<int>("damage")) {
			inphys = data.get<int>("damage");
		}
		if (data.get<int>("magical-damage")) {
			inmagical = data.get<int>("magical-damage");
		}
		inaspeed = data.get<double>("attack_cooldown");

		}
		catch(const std::exception& e)
		{
			std::cerr << "[ERROR] Missing value from input data! Make sure the JSON input data is valid!\n";
		}
		
    return Monster(innev,inhp,inphys,inmagic,indef,inaspeed);
}