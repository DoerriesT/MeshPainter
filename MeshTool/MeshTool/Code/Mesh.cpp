#include "Mesh.h"
#include "Utility.h"

std::shared_ptr<GLMesh> GLMesh::createMesh(const IndexedMesh &_indexedMesh)
{
	return std::shared_ptr<GLMesh>(new GLMesh(_indexedMesh));
}

GLMesh::~GLMesh()
{
	funcs->glBindVertexArray(VAO);
	funcs->glDisableVertexAttribArray(0);

	funcs->glBindBuffer(GL_ARRAY_BUFFER, 0);
	funcs->glDeleteBuffers(1, &EBO);
	funcs->glDeleteBuffers(1, &VBO);

	funcs->glBindVertexArray(0);
	funcs->glDeleteVertexArrays(1, &VAO);
}

void GLMesh::enableVertexAttribArrays() const
{
	assert(VAO);
	funcs->glBindVertexArray(VAO);
	funcs->glEnableVertexAttribArray(0);
	funcs->glEnableVertexAttribArray(1);
	funcs->glEnableVertexAttribArray(2);
}

void GLMesh::render() const
{
	funcs->glDrawElements(GL_TRIANGLES, (GLsizei)indexedMesh.indices.size(), GL_UNSIGNED_INT, NULL);
}

GLMesh::GLMesh(const IndexedMesh &_indexedMesh)
	:indexedMesh(_indexedMesh),
	funcs(getGLFunctions())
{
	// create buffers/arrays
	funcs->glGenVertexArrays(1, &VAO);
	funcs->glGenBuffers(1, &VBO);
	funcs->glGenBuffers(1, &EBO);
	funcs->glBindVertexArray(VAO);
	funcs->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	funcs->glBufferData(GL_ARRAY_BUFFER, indexedMesh.vertices.size() * sizeof(Vertex), indexedMesh.vertices.data(), GL_STATIC_DRAW);
	funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	funcs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexedMesh.indices.size() * sizeof(uint32_t), indexedMesh.indices.data(), GL_STATIC_DRAW);

	// vertex positions
	funcs->glEnableVertexAttribArray(0);
	funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// vertex normals
	funcs->glEnableVertexAttribArray(1);
	funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// vertex texture coord
	funcs->glEnableVertexAttribArray(2);
	funcs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	
	//// vertex tangent
	//funcs->glEnableVertexAttribArray(3);
	//funcs->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	funcs->glBindVertexArray(0);

	Utility::glErrorCheck();
}
