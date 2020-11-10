#include "Monster.h"
#include "JSON.h"

Monster Monster::parse(std::string filename)
{
    JSON data = JSON::parseFromFile(filename);
		std::string innev = "default";
		int inhp = 1;
		int indmg = 1;
		double inaspeed = 1.0;
		try
		{
		innev = data.get<std::string>("name");
		inhp = data.get<int>("health_points");
		indmg = data.get<int>("damage");
		inaspeed = data.get<double>("attack_cooldown");

		}
		catch(const std::exception& e)
		{
			std::cerr << "[ERROR] Missing value from input data! Make sure the JSON input data is valid!\n";
		}
		
    return Monster(innev,inhp,indmg,inaspeed);
}