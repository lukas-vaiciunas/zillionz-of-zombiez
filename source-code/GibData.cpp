#include "GibData.h"
#include <fstream>

GibData::GibData() :
	gibMap_()
{
	this->load_("data/gibs.txt");
}

const GibData::Gibs &GibData::getGibs(GibId id) const
{
	return gibMap_.find(id)->second;
}

void GibData::load_(const std::string &filePath)
{
	std::ifstream in(filePath);
	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in GibData!\n", filePath.c_str());
		return;
	}

	int numGibLists;
	in >> numGibLists;

	while (numGibLists--)
	{
		Gibs gibs;

		int gibId;
		int numGibPairs;

		in >> gibId >> numGibPairs;

		while (numGibPairs--)
		{
			int gibTextureId;
			int numGibs;

			in >> gibTextureId >> numGibs;

			gibs.emplace(gibTextureId, numGibs);
		}

		gibMap_.emplace(gibId, std::move(gibs));
	}

	in.close();
}