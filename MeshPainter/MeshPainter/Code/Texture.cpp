#include "Texture.h"
#include <algorithm>
#include <iostream>
#include <cassert>
#include <functional>
#include <stb_image.h>
#include <gli\texture.hpp>
#include <gli\load.hpp>
#include <cassert>
#include "Utility.h"


std::map<std::string, std::weak_ptr<Texture>> Texture::textureMap;
float Texture::anisotropicFiltering = 1.0f;

std::shared_ptr<Texture> Texture::createTexture(GLuint _id, GLenum _target)
{
	std::string idStr = std::to_string(_id);
	if (ContainerUtility::contains(textureMap, idStr))
	{
		return std::shared_ptr<Texture>(textureMap[idStr]);
	}
	else
	{
		std::shared_ptr<Texture> texture = std::shared_ptr<Texture>(new Texture(_id, _target));
		textureMap[idStr] = texture;
		return texture;
	}
}

std::shared_ptr<Texture> Texture::createTexture(const std::string &_filename, bool _instantLoading)
{
	if (ContainerUtility::contains(textureMap, _filename))
	{
		return std::shared_ptr<Texture>(textureMap[_filename]);
	}
	else
	{
		std::shared_ptr<Texture> texture = std::shared_ptr<Texture>(new Texture(_filename, _instantLoading));
		textureMap[_filename] = texture;
		return texture;
	}
}

Texture::Texture(GLuint _id, GLenum _target)
	:filepath(std::to_string(_id)), 
	id(_id),
	target(_target),
	funcs(getGLFunctions())
{
}

Texture::Texture(const std::string &_filename, bool _instantLoading)
	: filepath(_filename), funcs(getGLFunctions())
{
	bool isDDS;
	gli::texture gliTexture;
	unsigned char *stbiData;
	int width;
	int height;
	int channels;

	isDDS = Utility::getPathFileExtension(_filename) == "dds";

	if (!isDDS)
	{
		stbiData = stbi_load(_filename.c_str(), &width, &height, &channels, 0);
		assert(stbiData);
	}
	else
	{
		gliTexture = gli::load(_filename);
		assert(!gliTexture.empty());
	}

	if (isDDS)
	{
		initOpenGL(gliTexture);
	}
	else
	{
		initOpenGLFromData(stbiData, width, height, channels);
	}

	if (!isDDS)
	{
		stbi_image_free(stbiData);
	}
}

Texture::~Texture()
{
	ContainerUtility::remove(textureMap, filepath);
	glDeleteTextures(1, &id);
}

GLuint Texture::getId() const
{
	return id;
}

GLenum Texture::getTarget() const
{
	return target;
}

void Texture::setAnisotropicFilteringAll(float _anisotropicFiltering)
{
	if (anisotropicFiltering != _anisotropicFiltering)
	{
		for (auto &pair : textureMap)
		{
			pair.second.lock()->setAnisotropicFiltering(_anisotropicFiltering);
		}
		anisotropicFiltering = _anisotropicFiltering;
	}
}

void Texture::setAnisotropicFiltering(float _anisotropicFiltering)
{
	//if (GLAD_GL_EXT_texture_filter_anisotropic)
	//{
	//	glBindTexture(target, id);
	//	glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<GLfloat>(_anisotropicFiltering));
	//}
	//else
	//{
	//	std::cout << "OpenGL extension GL_EXT_texture_filter_anisotropic is not supported!" << std::endl;
	//}
}

void Texture::initOpenGL(const gli::texture &_file)
{
	const gli::texture &texture = _file;

	gli::gl glTranslator(gli::gl::PROFILE_GL33);
	gli::gl::format const format = glTranslator.translate(texture.format(), texture.swizzles());

	GLenum textureType = glTranslator.translate(texture.target());
	target = textureType;
	id = 0;

	funcs->glGenTextures(1, &id);
	funcs->glBindTexture(textureType, id);
	// Base and max level are not supported by OpenGL ES 2.0
	funcs->glTexParameteri(textureType, GL_TEXTURE_BASE_LEVEL, 0);
	funcs->glTexParameteri(textureType, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(texture.levels() - 1));
	//Texture swizzle is not supported by OpenGL ES 2.0 and OpenGL 3.2
	funcs->glTexParameteri(textureType, GL_TEXTURE_SWIZZLE_R, format.Swizzles[0]);
	funcs->glTexParameteri(textureType, GL_TEXTURE_SWIZZLE_G, format.Swizzles[1]);
	funcs->glTexParameteri(textureType, GL_TEXTURE_SWIZZLE_B, format.Swizzles[2]);
	funcs->glTexParameteri(textureType, GL_TEXTURE_SWIZZLE_A, format.Swizzles[3]);
	funcs->glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	funcs->glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	setAnisotropicFiltering(anisotropicFiltering);

	glm::tvec3<GLsizei> const extent(texture.extent());
	GLsizei const totalFaces = static_cast<GLsizei>(texture.layers() * texture.faces());

	for (std::size_t layer = 0; layer < texture.layers(); ++layer)
	{
		for (std::size_t level = 0; level < texture.levels(); ++level)
		{
			for (std::size_t face = 0; face < texture.faces(); ++face)
			{
				GLsizei const LayerGL = static_cast<GLsizei>(layer);
				glm::tvec3<GLsizei> extent(texture.extent(level));
				textureType = gli::is_target_cube(texture.target()) ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face) : textureType;

				switch (texture.target())
				{
					case gli::TARGET_1D:
					{
						if (gli::is_compressed(texture.format()))
						{
							funcs->glCompressedTexImage1D(textureType, format.Internal, static_cast<GLint>(level), 0, extent.x, static_cast<GLsizei>(texture.size(level)), texture.data(layer, face, level));
						}
						else
						{
							funcs->glTexImage1D(textureType, static_cast<GLint>(level), format.Internal, extent.x, 0, format.External, format.Type, texture.data(layer, face, level));
						}
						break;
					}
					case gli::TARGET_1D_ARRAY:
					case gli::TARGET_2D:
					case gli::TARGET_CUBE:
					{
						if (gli::is_compressed(texture.format()))
						{
							funcs->glCompressedTexImage2D(textureType, static_cast<GLint>(level), format.Internal, extent.x, texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : extent.y, 0, static_cast<GLsizei>(texture.size(level)), texture.data(layer, face, level));
						}
						else
						{
							funcs->glTexImage2D(textureType, static_cast<GLint>(level), format.Internal, extent.x, texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : extent.y, 0, format.External, format.Type, texture.data(layer, face, level));
						}
						break;
					}
					case gli::TARGET_2D_ARRAY:
					case gli::TARGET_3D:
					case gli::TARGET_CUBE_ARRAY:
					{
						if (gli::is_compressed(texture.format()))
						{
							funcs->glCompressedTexImage3D(textureType, static_cast<GLint>(level), format.Internal, extent.x, extent.y, texture.target() == gli::TARGET_3D ? extent.z : LayerGL, 0, static_cast<GLsizei>(texture.size(level)), texture.data(layer, face, level));
						}
						else
						{
							funcs->glTexImage3D(textureType, static_cast<GLint>(level), format.Internal, extent.x, extent.y, texture.target() == gli::TARGET_3D ? extent.z : LayerGL, 0, format.External, format.Type, texture.data(layer, face, level));
						}
						break;
					}
					default:
					{
						assert(false);
						break;
					}
				}
			}
		}
	}
}

void Texture::initOpenGLFromData(unsigned char *_stbiData, int _width, int _height, int _channels)
{
	target = GL_TEXTURE_2D;
	id = 0;

	funcs->glGenTextures(1, &id);
	funcs->glBindTexture(GL_TEXTURE_2D, id);
	GLenum format;

	setAnisotropicFiltering(anisotropicFiltering);

	switch (_channels)
	{
		case 4:
			format = GL_RGBA;
			break;
		case 3:
			format = GL_RGB;
			break;
		default:
			format = GL_RED;
			break;
	}

	funcs->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	funcs->glTexImage2D(target, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, _stbiData);

	funcs->glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	funcs->glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	funcs->glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	funcs->glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	funcs->glGenerateMipmap(target);
}
