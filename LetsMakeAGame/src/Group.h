#pragma once

#include "DataGroupType.h"
class Group
{
public:
	DataGroupType m_type;
	Group() {}
	Group(DataGroupType type) : m_type(type) {}

	virtual int NumberOfDataInGroup() = 0;
	virtual void AddToGroup(std::string str) = 0;

	virtual void Draw() = 0;
};