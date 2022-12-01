#include "FoodData.h"
#include <fstream>

FoodData::FoodData() :
	foods_()
{
	this->load_("data/food.txt");
}

FoodData &FoodData::getInstance()
{
	static FoodData instance;
	return instance;
}

const Food &FoodData::getFood(Id id) const
{
	return foods_.find(id)->second;
}

void FoodData::load_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in FoodData!\n", filePath.c_str());
		return;
	}

	int32_t numFoods;
	in >> numFoods;

	while (numFoods--)
	{
		int32_t id;
		float healAmount;
		std::string name;

		in >> id >> healAmount >> name;

		foods_.emplace(id, Food(healAmount, id, name));
	}

	in.close();
}