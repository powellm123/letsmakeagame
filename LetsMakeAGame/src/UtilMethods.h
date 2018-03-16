#pragma once
#include <string>

class UtilMethods
{
public:
	static std::string ToLower(std::string str);
	static std::string ToUpper(std::string str);
	static size_t constexpr const_hash(char const *input)
	{
		return *input ? static_cast<size_t>(*input) + 33 * const_hash(input + 1) : 5381;
	}
private:
	const static char a = 'a';
	const static char A = 'A';
	const static char z = 'z';
	const static char Z = 'Z';
};