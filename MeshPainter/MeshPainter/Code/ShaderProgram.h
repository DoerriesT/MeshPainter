#pragma once
#include <string>
#include <vector>
#include <glm\mat4x4.hpp>
#include <memory>
#include "GLFunctions.h"

class ShaderProgram
{
public:
	static std::shared_ptr<ShaderProgram> createShaderProgram(const char *_vertexShaderPath,
		const char *_fragmentShaderPath,
		const char *_tesselationControlShaderPath = nullptr,
		const char *_tesselationEvaluationShaderPath = nullptr,
		const char *_geometryShaderPath = nullptr);
	static std::shared_ptr<ShaderProgram> createShaderProgram(const char *_computeShaderPath);

	ShaderProgram(const ShaderProgram &) = delete;
	ShaderProgram(const ShaderProgram &&) = delete;
	ShaderProgram &operator= (const ShaderProgram &) = delete;
	ShaderProgram &operator= (const ShaderProgram &&) = delete;
	~ShaderProgram();
	void bind();
	GLuint getId() const;
	const GLint createUniform(const std::string &_name) const;
	void setUniform(const GLint &_location, const GLboolean &_value) const;
	void setUniform(const GLint &_location, const GLint &_value) const;
	void setUniform(const GLint &_location, GLuint _value) const;
	void setUniform(const GLint &_location, const GLfloat &value) const;
	void setUniform(const GLint &_location, const glm::mat2 &_value) const;
	void setUniform(const GLint &_location, const glm::mat3 &_value) const;
	void setUniform(const GLint &_location, const glm::mat4 &_value) const;
	void setUniform(const GLint &_location, const glm::vec2 &_value) const;
	void setUniform(const GLint &_location, const glm::vec3 &_value) const;
	void setUniform(const GLint &_location, const glm::vec4 &_value) const;

private:
	QOpenGLFunctions_3_3_Core *funcs;
	GLuint programId;

	explicit ShaderProgram(const char *_vertexShaderPath,
		const char *_fragmentShaderPath,
		const char *_tesselationControlShaderPath = nullptr,
		const char *_tesselationEvaluationShaderPath = nullptr,
		const char *_geometryShaderPath = nullptr);
	explicit ShaderProgram(const char *_computeShaderPath);
	GLuint createShader(GLenum _type, const char *_shaderPath);
	void statusCheck(GLenum _type);
};