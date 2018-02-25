#pragma once
#include <string>

class UtilMethods
{
public:
	static std::string ToLower(std::string str);
	static std::string ToUpper(std::string str);

private:
	const static char a = 'a';
	const static char A = 'A';
	const static char z = 'z';
	const static char Z = 'Z';
};