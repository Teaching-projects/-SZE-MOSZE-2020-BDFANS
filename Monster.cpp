#include "Monster.h"
#include "JSON.h"

Monster Monster::parse(std::string filename)
{
    JSON data = JSON::parseFromFile(filename);
		std::string innev = "default";
		int inhp = 1;
		int indmg = 1;
		double inaspeed = 1.0;
		if(data.count("name") > 0)
		{
		innev = data.get<std::string>("name");
		}
		if(data.count("health_points") > 0)
		{
		inhp = data.get<int>("health_points");
		}
		if(data.count("damage") > 0)
		{
		indmg = data.get<int>("damage");
		}
		if(data.count("attack_cooldown") > 0)
		{
		inaspeed = data.get<double>("attack_cooldown");
		}
        return Monster(innev,inhp,indmg,inaspeed);
}