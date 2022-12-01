#include "RandGen.h"

RandGen::RandGen() :
	eng_(std::random_device()())
{}

RandGen &RandGen::getInstance()
{
	static RandGen instance;
	return instance;
}

std::mt19937 &RandGen::getEng()
{
	return eng_;
}