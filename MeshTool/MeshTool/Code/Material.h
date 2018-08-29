#pragma once
#include <glm\vec4.hpp>
#include <glm\vec3.hpp>
#include <string>
#include <memory>

class Texture;

class Material
{
public:
	static const std::uint32_t ALBEDO;
	static const std::uint32_t NORMAL;
	static const std::uint32_t METALLIC;
	static const std::uint32_t ROUGHNESS;
	static const std::uint32_t AO;
	static const std::uint32_t EMISSIVE;
	static const std::uint32_t DISPLACEMENT;

	explicit Material(const glm::vec4 &_albedo = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), float _metallic = 0.0f, float _roughness = 0.0f, const glm::vec3 &_emissive = glm::vec3(0.0f));
	explicit Material(const std::shared_ptr<Texture> &_albedoMap,
		const std::shared_ptr<Texture> &_normalMap = nullptr,
		const std::shared_ptr<Texture> &_metallicMap = nullptr,
		const std::shared_ptr<Texture> &_roughnessMap = nullptr,
		const std::shared_ptr<Texture> &_aoMap = nullptr,
		const std::shared_ptr<Texture> &_emissiveMap = nullptr,
		const std::shared_ptr<Texture> &_displacementMap = nullptr);
	explicit Material(const std::string &_basePath, std::uint32_t _flags);
	const std::shared_ptr<Texture> getAlbedoMap() const;
	const std::shared_ptr<Texture> getNormalMap() const;
	const std::shared_ptr<Texture> getMetallicMap() const;
	const std::shared_ptr<Texture> getRoughnessMap() const;
	const std::shared_ptr<Texture> getAoMap() const;
	const std::shared_ptr<Texture> getEmissiveMap() const;
	const std::shared_ptr<Texture> getDisplacementMap() const;
	const std::uint32_t getMapBitField() const;
	const glm::vec4 &getAlbedo() const;
	float getMetallic() const;
	float getRoughness() const;
	const glm::vec3 &getEmissive() const;
	void setAlbedoMap(const std::shared_ptr<Texture> &_albedoMap);
	void setNormalMap(const std::shared_ptr<Texture> &_normalMap);
	void setMetallicMap(const std::shared_ptr<Texture> &_metallicMap);
	void setRoughnessMap(const std::shared_ptr<Texture> &_roughnessMap);
	void setAoMap(const std::shared_ptr<Texture> &_aoMap);
	void setEmissiveMap(const std::shared_ptr<Texture> &_emissiveMap);
	void setDisplacementMap(const std::shared_ptr<Texture> &_displacementMap);
	void setAlbedo(const glm::vec4 &_albedo);
	void setMetallic(float _metallic);
	void setRoughness(float _roughness);
	void setEmissive(const glm::vec3 &_emissive);
	void bindTextures() const;

private:
	glm::vec4 albedo;
	float metallic;
	float roughness;
	glm::vec3 emissive;
	std::shared_ptr<Texture> albedoMap;
	std::shared_ptr<Texture> normalMap;
	std::shared_ptr<Texture> metallicMap;
	std::shared_ptr<Texture> roughnessMap;
	std::shared_ptr<Texture> aoMap;
	std::shared_ptr<Texture> emissiveMap;
	std::shared_ptr<Texture> displacementMap;
};