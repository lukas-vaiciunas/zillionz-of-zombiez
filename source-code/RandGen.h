#pragma once

#include <random>

class RandGen
{
public:
	RandGen(const RandGen &) = delete;
	RandGen &operator=(const RandGen &) = delete;

	static RandGen &getInstance();

	std::mt19937 &getEng();
private:
	std::mt19937 eng_;

	RandGen();
	~RandGen() {}
};