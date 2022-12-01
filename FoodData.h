#pragma once

#include "Food.h"

class FoodData
{
public:
	typedef uint16_t Id;

	FoodData(const FoodData &) = delete;
	FoodData &operator=(const FoodData &) = delete;

	static FoodData &getInstance();

	const Food &getFood(Id id) const;
private:
	std::unordered_map<Id, Food> foods_;

	FoodData();
	~FoodData() {}

	void load_(const std::string &filePath);
};