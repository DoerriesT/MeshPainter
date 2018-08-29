#pragma once
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <vector>
#include <memory>
#include "GLFunctions.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct IndexedMesh
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};

class GLMesh
{
public:
	static std::shared_ptr<GLMesh> createMesh(const IndexedMesh &_indexedMesh);

	GLMesh(const GLMesh &) = delete;
	GLMesh(const GLMesh &&) = delete;
	GLMesh &operator= (const GLMesh &) = delete;
	GLMesh &operator= (const GLMesh &&) = delete;
	~GLMesh();
	void enableVertexAttribArrays() const;
	void render() const;

private:
	QOpenGLFunctions_3_3_Core *funcs;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	IndexedMesh indexedMesh;

	explicit GLMesh(const IndexedMesh &_indexedMesh);
};