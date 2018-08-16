#pragma once
#include <vector>

struct IndexedMesh;

struct HalfEdgeMesh
{
	explicit HalfEdgeMesh(const IndexedMesh &_indexedMesh);
	~HalfEdgeMesh();

	struct HalfEdge;

	struct Vertex
	{
		uint32_t index;
		HalfEdge *halfEdge;
	};

	struct Face
	{
		HalfEdge *halfEdge;
	};

	struct HalfEdge
	{
		HalfEdge *twin;
		HalfEdge *next;
		Vertex *origin;
		Face *face;
	};

	std::vector<HalfEdgeMesh::Vertex *> vertices;
	std::vector<HalfEdgeMesh::Face *> faces;
	std::vector<HalfEdgeMesh::HalfEdge *> halfEdges;
};