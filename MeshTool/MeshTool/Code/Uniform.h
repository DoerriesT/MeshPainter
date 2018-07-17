#pragma once
#include <string>
#include "ShaderProgram.h"

template<typename Type>
class Uniform
{
public:
	typedef Type ValueType;
	
	Uniform(const std::string &_name = "");
	void create(const std::shared_ptr<ShaderProgram> &_shaderProgram);
	void set(const Type &_value);
	bool isValid();

private:
	std::shared_ptr<ShaderProgram> shaderProgram;
	GLint location;
	Type value;
	std::string name;
	bool firstTime;
};

template<typename Type>
inline Uniform<Type>::Uniform(const std::string &_name)
	:location(-1), name(_name),  firstTime(true)
{
}

template<typename Type>
inline void Uniform<Type>::create(const std::shared_ptr<ShaderProgram> &_shaderProgram)
{
	shaderProgram = _shaderProgram;
	location = shaderProgram->createUniform(name);
	//assert(isValid());
}

template<typename Type>
inline void Uniform<Type>::set(const Type &_value)
{
	//assert(isValid());
	if (firstTime || value != _value)
	{
		firstTime = false;
		value = _value;
		shaderProgram->setUniform(location, value);
	}
}

template<typename Type>
inline bool Uniform<Type>::isValid()
{
	return location != -1;
}