#include "Material.h"
#include "Texture.h"
#include "GLFunctions.h"

const std::uint32_t Material::ALBEDO = 1 << 0;
const std::uint32_t Material::NORMAL = 1 << 1;
const std::uint32_t Material::METALLIC = 1 << 2;
const std::uint32_t Material::ROUGHNESS = 1 << 3;
const std::uint32_t Material::AO = 1 << 4;
const std::uint32_t Material::EMISSIVE = 1 << 5;
const std::uint32_t Material::DISPLACEMENT = 1 << 6;

Material::Material(const glm::vec4 &_albedo, float _metallic, float _roughness, const glm::vec3 &_emissive)
	: albedo(_albedo), metallic(_metallic), roughness(_roughness), emissive(_emissive)
{
}

Material::Material(const std::shared_ptr<Texture> &_albedoMap, 
	const std::shared_ptr<Texture> &_normalMap, 
	const std::shared_ptr<Texture> &_metallicMap, 
	const std::shared_ptr<Texture> &_roughnessMap, 
	const std::shared_ptr<Texture> &_aoMap, 
	const std::shared_ptr<Texture> &_emissiveMap,
	const std::shared_ptr<Texture> &_displacementMap)
	: albedo(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), 
	metallic(0.0f), 
	roughness(0.0f), 
	albedoMap(_albedoMap), 
	normalMap(_normalMap), 
	metallicMap(_metallicMap), 
	roughnessMap(_roughnessMap), 
	aoMap(_aoMap), 
	emissiveMap(_emissiveMap),
	displacementMap(_displacementMap)
{
}

Material::Material(const std::string &_basePath, std::uint32_t _flags)
	: albedo(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), metallic(0.0f), roughness(0.0f)
{
	std::string albedoPath = _basePath + "_a.dds";
	std::string normalPath = _basePath + "_n.dds";
	std::string metallicPath = _basePath + "_m.dds";
	std::string roughnessPath = _basePath + "_r.dds";
	std::string aoPath = _basePath + "_ao.dds";
	std::string emissivePath = _basePath + "_e.dds";
	std::string displacementPath = _basePath + "_d.dds";

	if ((_flags & ALBEDO) == ALBEDO)
	{
		albedoMap = Texture::createTexture(albedoPath.c_str());
	}
	if ((_flags & NORMAL) == NORMAL)
	{
		normalMap = Texture::createTexture(normalPath.c_str());
	}
	if ((_flags & METALLIC) == METALLIC)
	{
		metallicMap = Texture::createTexture(metallicPath.c_str());
	}
	if ((_flags & ROUGHNESS) == ROUGHNESS)
	{
		roughnessMap = Texture::createTexture(roughnessPath.c_str());
	}
	if ((_flags & AO) == AO)
	{
		aoMap = Texture::createTexture(aoPath.c_str());
	}
	if ((_flags & EMISSIVE) == EMISSIVE)
	{
		emissiveMap = Texture::createTexture(emissivePath.c_str());
	}
	if ((_flags & DISPLACEMENT) == DISPLACEMENT)
	{
		displacementMap = Texture::createTexture(displacementPath.c_str());
	}
}

const std::shared_ptr<Texture> Material::getAlbedoMap() const
{
	return albedoMap;
}

const std::shared_ptr<Texture> Material::getNormalMap() const
{
	return normalMap;
}

const std::shared_ptr<Texture> Material::getMetallicMap() const
{
	return metallicMap;
}

const std::shared_ptr<Texture> Material::getRoughnessMap() const
{
	return roughnessMap;
}

const std::shared_ptr<Texture> Material::getAoMap() const
{
	return aoMap;
}

const std::shared_ptr<Texture> Material::getEmissiveMap() const
{
	return emissiveMap;
}

const std::shared_ptr<Texture> Material::getDisplacementMap() const
{
	return displacementMap;
}

const std::uint32_t Material::getMapBitField() const
{
	std::uint32_t field = 0;
	if (albedoMap)
	{
		field |= ALBEDO;
	}
	if (normalMap)
	{
		field |= NORMAL;
	}
	if (metallicMap)
	{
		field |= METALLIC;
	}
	if (roughnessMap)
	{
		field |= ROUGHNESS;
	}
	if (aoMap)
	{
		field |= AO;
	}
	if (emissiveMap)
	{
		field |= EMISSIVE;
	}
	if (displacementMap)
	{
		field |= DISPLACEMENT;
	}
	return field;
}

const glm::vec4 &Material::getAlbedo() const
{
	return albedo;
}

float Material::getMetallic() const
{
	return metallic;
}

float Material::getRoughness() const
{
	return roughness;
}

const glm::vec3 &Material::getEmissive() const
{
	return emissive;
}

void Material::setAlbedoMap(const std::shared_ptr<Texture> &_albedoMap)
{
	albedoMap = _albedoMap;
}

void Material::setNormalMap(const std::shared_ptr<Texture> &_normalMap)
{
	normalMap = _normalMap;
}

void Material::setMetallicMap(const std::shared_ptr<Texture> &_metallicMap)
{
	metallicMap = _metallicMap;
}

void Material::setRoughnessMap(const std::shared_ptr<Texture> &_roughnessMap)
{
	roughnessMap = _roughnessMap;
}

void Material::setAoMap(const std::shared_ptr<Texture> &_aoMap)
{
	aoMap = _aoMap;
}

void Material::setEmissiveMap(const std::shared_ptr<Texture> &_emissiveMap)
{
	emissiveMap = _emissiveMap;
}

void Material::setDisplacementMap(const std::shared_ptr<Texture> &_displacementMap)
{
	displacementMap = _displacementMap;
}

void Material::setAlbedo(const glm::vec4 & _albedo)
{
	albedo = _albedo;
}

void Material::setMetallic(float _metallic)
{
	metallic = _metallic;
}

void Material::setRoughness(float _roughness)
{
	roughness = _roughness;
}

void Material::setEmissive(const glm::vec3 &_emissive)
{
	emissive = _emissive;
}

void Material::bindTextures() const
{
	auto funcs = getGLFunctions();
	if (albedoMap)
	{
		funcs->glActiveTexture(GL_TEXTURE0);
		glBindTexture(albedoMap->getTarget(), albedoMap->getId());
	}
	if (normalMap)
	{
		funcs->glActiveTexture(GL_TEXTURE1);
		glBindTexture(normalMap->getTarget(), normalMap->getId());
	}
	if (metallicMap)
	{
		funcs->glActiveTexture(GL_TEXTURE2);
		glBindTexture(metallicMap->getTarget(), metallicMap->getId());
	}
	if (roughnessMap)
	{
		funcs->glActiveTexture(GL_TEXTURE3);
		glBindTexture(roughnessMap->getTarget(), roughnessMap->getId());
	}
	if (aoMap)
	{
		funcs->glActiveTexture(GL_TEXTURE4);
		glBindTexture(aoMap->getTarget(), aoMap->getId());
	}
	if (emissiveMap)
	{
		funcs->glActiveTexture(GL_TEXTURE5);
		glBindTexture(emissiveMap->getTarget(), emissiveMap->getId());
	}
	if (displacementMap)
	{
		funcs->glActiveTexture(GL_TEXTURE6);
		glBindTexture(displacementMap->getTarget(), displacementMap->getId());
	}
}
