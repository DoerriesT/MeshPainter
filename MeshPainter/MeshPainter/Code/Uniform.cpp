#include "Uniform.h"

UniformMaterial::UniformMaterial(const std::string &_name)
	:albedo(_name + ".albedo"),
	metallic(_name + ".metallic"),
	roughness(_name + ".roughness"),
	emissive(_name + ".emissive"),
	mapBitField(_name + ".mapBitField"),
	name(_name),
	firstTime(true)
{
}

void UniformMaterial::create(const std::shared_ptr<ShaderProgram> &_shaderProgram)
{
	shaderProgram = _shaderProgram;
	albedo.create(shaderProgram);
	metallic.create(shaderProgram);
	roughness.create(shaderProgram);
	emissive.create(shaderProgram);
	mapBitField.create(shaderProgram);
}

void UniformMaterial::set(const Material *_value)
{
	albedo.set(_value->getAlbedo());
	metallic.set(_value->getMetallic());
	roughness.set(_value->getRoughness());
	emissive.set(_value->getEmissive());
	mapBitField.set(_value->getMapBitField());
}

bool UniformMaterial::isValid()
{
	return albedo.isValid() &&
		metallic.isValid() &&
		roughness.isValid() &&
		emissive.isValid() &&
		mapBitField.isValid();
}
