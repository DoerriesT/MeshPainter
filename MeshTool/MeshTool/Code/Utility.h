#pragma once
#include <vector>

namespace Utility
{
	std::vector<char> readTextFile(const std::string &_filename);

	std::vector<std::string> split(const std::string &str, const std::string &seperator);

	void glErrorCheck();
}