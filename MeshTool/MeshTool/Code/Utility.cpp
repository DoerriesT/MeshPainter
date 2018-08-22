#include "Utility.h"
#include <fstream>
#include <cassert>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <GLFunctions.h>

std::vector<char> Utility::readTextFile(const std::string & _filename)
{
	std::ifstream file(_filename, std::ios::ate);
	file.exceptions(std::ifstream::badbit);

	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file " + _filename + "!");
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer;
	buffer.reserve(fileSize);
	file.seekg(0);

	//file.read(buffer, fileSize);
	char c;
	size_t position = 0;
	while (file.get(c))
	{
		//if (c != '\r') {
		buffer.push_back(c);
		++position;
		assert(position <= fileSize);
	}
	buffer.push_back('\0');

	file.close();

	return buffer;
}

//base code from Fox32 (https://stackoverflow.com/a/5167641)
std::vector<std::string> Utility::split(const std::string & str, const std::string & seperator)
{
	std::vector<std::string> output;
	std::string::size_type prev_pos = 0, pos = 0;
	while ((pos = str.find(seperator, pos)) != std::string::npos)
	{
		std::string substring(str.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = pos += seperator.size();
	}
	output.push_back(str.substr(prev_pos, pos - prev_pos));
	return output;
}

std::string Utility::getPathFileExtension(const std::string & filePath)
{
	return split(filePath, ".").back();
}

std::string Utility::getFormatedTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	struct tm buf;
	localtime_s(&buf, &in_time_t);

	std::stringstream ss;
	ss << std::put_time(&buf, "%Y-%m-%d-%H-%M-%S");
	return ss.str();
}

void Utility::glErrorCheck()
{
	switch (getGLFunctions()->glGetError())
	{
	case (GL_INVALID_ENUM):
		assert(false);
		break;
	case (GL_INVALID_VALUE):
		assert(false);
		break;
	case (GL_INVALID_OPERATION):
		assert(false);
		break;
	case (GL_OUT_OF_MEMORY):
		assert(false);
		break;
	case (GL_INVALID_FRAMEBUFFER_OPERATION):
		assert(false);
		break;
	}
}
