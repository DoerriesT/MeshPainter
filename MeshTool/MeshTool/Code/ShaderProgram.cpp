#include <glm\gtc\type_ptr.hpp>
#include <glm\ext.hpp>
#include <cassert>
#include <iostream>
#include "ShaderProgram.h"
#include "Utility.h"


ShaderProgram::ShaderProgram(const char *_vertexShaderPath,
	const char *_fragmentShaderPath,
	const char *_tesselationControlShaderPath,
	const char *_tesselationEvaluationShaderPath,
	const char *_geometryShaderPath)
	:funcs(getGLFunctions())
{
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, _vertexShaderPath);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, _fragmentShaderPath);
	GLuint tessControlShader = 0;
	GLuint tessEvalShader = 0;
	GLuint geometryShader = 0;

	// make sure we dont try to create a program with only control shader
	assert(_tesselationEvaluationShaderPath ? true : !bool(_tesselationControlShaderPath));

	if (_tesselationControlShaderPath)
	{
		tessControlShader = createShader(GL_TESS_CONTROL_SHADER, _tesselationControlShaderPath);
	}
	if (_tesselationEvaluationShaderPath)
	{
		tessEvalShader = createShader(GL_TESS_EVALUATION_SHADER, _tesselationEvaluationShaderPath);
	}
	if (_geometryShaderPath)
	{
		geometryShader = createShader(GL_GEOMETRY_SHADER, _geometryShaderPath);
	}

	// shader Program
	programId = funcs->glCreateProgram();
	funcs->glAttachShader(programId, vertexShader);
	funcs->glAttachShader(programId, fragmentShader);
	if (_tesselationControlShaderPath)
	{
		funcs->glAttachShader(programId, tessControlShader);
	}
	if (_tesselationEvaluationShaderPath)
	{
		funcs->glAttachShader(programId, tessEvalShader);
	}
	if (_geometryShaderPath)
	{
		funcs->glAttachShader(programId, geometryShader);
	}

	funcs->glLinkProgram(programId);
	statusCheck(GL_LINK_STATUS);

	// delete the shaders as they're linked into our program now and no longer necessery
	funcs->glDetachShader(programId, vertexShader);
	funcs->glDetachShader(programId, fragmentShader);
	if (_tesselationControlShaderPath)
	{
		funcs->glDetachShader(programId, tessControlShader);
		funcs->glDeleteShader(tessControlShader);
	}
	if (_tesselationEvaluationShaderPath)
	{
		funcs->glDetachShader(programId, tessEvalShader);
		funcs->glDeleteShader(tessEvalShader);
	}
	if (_geometryShaderPath)
	{
		funcs->glDetachShader(programId, geometryShader);
		funcs->glDeleteShader(geometryShader);
	}
	funcs->glDeleteShader(vertexShader);
	funcs->glDeleteShader(fragmentShader);

	// validate program
	funcs->glValidateProgram(programId);
	statusCheck(GL_VALIDATE_STATUS);
}

ShaderProgram::ShaderProgram(const char *_computeShaderPath)
{
	GLuint computeShader = createShader(GL_COMPUTE_SHADER, _computeShaderPath);

	// shader Program
	programId = funcs->glCreateProgram();
	funcs->glAttachShader(programId, computeShader);

	funcs->glLinkProgram(programId);
	statusCheck(GL_LINK_STATUS);

	// delete the shaders as they're linked into our program now and no longer necessery
	funcs->glDetachShader(programId, computeShader);
	funcs->glDeleteShader(computeShader);

	// validate program
	funcs->glValidateProgram(programId);
	statusCheck(GL_VALIDATE_STATUS);
}

GLuint ShaderProgram::createShader(GLenum _type, const char *_shaderPath)
{
	GLuint shader = funcs->glCreateShader(_type);

	std::vector<char> data = Utility::readTextFile(_shaderPath);
	const char *shaderCode = data.data();
	funcs->glShaderSource(shader, 1, &shaderCode, NULL);
	funcs->glCompileShader(shader);

	// print compile errors if any
	GLint success;
	funcs->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		funcs->glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << _shaderPath << "\n" << infoLog << std::endl;
		assert(false);
	};

	return shader;
}

void ShaderProgram::statusCheck(GLenum _type)
{
	GLint success;
	funcs->glGetProgramiv(programId, _type, &success);
	if (!success)
	{
		GLchar infoLog[512];
		funcs->glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
		if (_type == GL_LINK_STATUS)
		{
			std::cout << "WARNING::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		else if (_type == GL_VALIDATE_STATUS)
		{
			std::cout << "WARNING::SHADER::PROGRAM::VALIDATION_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << infoLog << std::endl;
		}
	}
}

std::shared_ptr<ShaderProgram> ShaderProgram::createShaderProgram(const char *_vertexShaderPath,
	const char *_fragmentShaderPath,
	const char *_tesselationControlShaderPath,
	const char *_tesselationEvaluationShaderPath,
	const char *_geometryShaderPath)
{
	return std::shared_ptr<ShaderProgram>(new ShaderProgram(_vertexShaderPath, _fragmentShaderPath, _tesselationControlShaderPath, _tesselationEvaluationShaderPath, _geometryShaderPath));
}

std::shared_ptr<ShaderProgram> ShaderProgram::createShaderProgram(const char *_computeShaderPath)
{
	return std::shared_ptr<ShaderProgram>(new ShaderProgram(_computeShaderPath));
}

ShaderProgram::~ShaderProgram()
{
	funcs->glDeleteProgram(programId);
}

void ShaderProgram::bind()
{
	funcs->glUseProgram(programId);
}

GLuint ShaderProgram::getId() const
{
	return programId;
}

const GLint ShaderProgram::createUniform(const std::string &_name) const
{
	return funcs->glGetUniformLocation(programId, _name.c_str());
}

void ShaderProgram::setUniform(const GLint &_location, const GLboolean &_value) const
{
	funcs->glUniform1i(_location, _value);
}

void ShaderProgram::setUniform(const GLint &_location, const GLint &_value) const
{
	funcs->glUniform1i(_location, _value);
}

void ShaderProgram::setUniform(const GLint &_location, GLuint _value) const
{
	funcs->glUniform1ui(_location, _value);
}

void ShaderProgram::setUniform(const GLint &_location, const GLfloat &_value) const
{
	funcs->glUniform1f(_location, _value);
}

void ShaderProgram::setUniform(const GLint &_location, const glm::mat3 &_value) const
{
	funcs->glUniformMatrix3fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}

void ShaderProgram::setUniform(const GLint &_location, const glm::mat4 &_value) const
{
	funcs->glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}

void ShaderProgram::setUniform(const GLint &_location, const glm::vec2 &_value) const
{
	funcs->glUniform2f(_location, _value.x, _value.y);
}

void ShaderProgram::setUniform(const GLint &_location, const glm::vec3 &_value) const
{
	funcs->glUniform3f(_location, _value.x, _value.y, _value.z);
}

void ShaderProgram::setUniform(const GLint &_location, const glm::vec4 &_value) const
{
	funcs->glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
}