#pragma once

#include <string>
#include <fstream>

class DataGroupType
{
public:
	enum DATATYPE {STRING, POSITION, BOX, NUMBER};
	std::string groupName;
	DATATYPE dataType;
	bool singleItem;

	static void SaveRSDataGroupType(std::ofstream& file, DataGroupType dataGroupType);
	static DataGroupType LoadRSDataGroupType(std::ifstream& file);
};