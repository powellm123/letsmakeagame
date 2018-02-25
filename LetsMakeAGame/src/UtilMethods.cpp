
#include "UtilMethods.h"

std::string UtilMethods::ToLower(std::string str)
{
	char *c = new char[str.size()+1];
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] > A && str[i] < Z)
		{
			c[i] = (a - A) + str[i];
		}
		else
			c[i] = str[i];
	}
	c[str.size()] = 0;
	return std::string(c);
}

std::string UtilMethods::ToUpper(std::string str)
{
	char *c = new char[str.size()];
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] > a && str[i] < z)
		{
			c[i] = str[i] - (a - A);
		}
		else
			c[i] = str[i];
	}

	c[str.size()] = 0;
	return std::string(c);

}