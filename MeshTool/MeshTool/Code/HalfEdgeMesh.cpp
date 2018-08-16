#include "HalfEdgeMesh.h"
#include <map>
#include <set>
#include "Mesh.h"

HalfEdgeMesh::HalfEdgeMesh(const IndexedMesh &_indexedMesh)
{
	assert(_indexedMesh.indices.size() % 3 == 0);

	std::map<std::pair<uint32_t, uint32_t>, HalfEdge *> halfEdgeMap;
	std::map<uint32_t, Vertex *> vertexMap;

	for (unsigned int i = 0; i < _indexedMesh.indices.size(); i += 3)
	{
		// local copy of indices
		uint32_t indices[3] = { _indexedMesh.indices[i], _indexedMesh.indices[i + 1], _indexedMesh.indices[i + 2] };

		// get pointer to vertices
		Vertex *v0 = vertexMap[indices[0]];
		Vertex *v1 = vertexMap[indices[1]];
		Vertex *v2 = vertexMap[indices[2]];

		// if vertices do not yet exist, create them
		if (!v0)
		{
			vertexMap[indices[0]] = v0 = new Vertex();
			v0->index = indices[0];
		}
		if (!v1)
		{
			vertexMap[indices[1]] = v1 = new Vertex();
			v1->index = indices[1];
		}
		if (!v2)
		{
			vertexMap[indices[2]] = v2 = new Vertex();
			v2->index = indices[2];
		}

		// create face
		Face *face = new Face();
		faces.push_back(face);

		// create half edges
		assert(halfEdgeMap.find(std::make_pair(indices[0], indices[1])) == halfEdgeMap.end());
		assert(halfEdgeMap.find(std::make_pair(indices[1], indices[2])) == halfEdgeMap.end());
		assert(halfEdgeMap.find(std::make_pair(indices[2], indices[0])) == halfEdgeMap.end());
		HalfEdge *he0 = new HalfEdge();
		HalfEdge *he1 = new HalfEdge();
		HalfEdge *he2 = new HalfEdge();
		halfEdgeMap[{indices[0], indices[1]}] = he0;
		halfEdgeMap[{indices[1], indices[2]}] = he1;
		halfEdgeMap[{indices[2], indices[0]}] = he2;
		assert(he0 && he1 && he2);

		// set half edge member data
		he0->next = he1;
		he0->origin = v0;
		he0->face = face;
		he1->next = he2;
		he1->origin = v1;
		he1->face = face;
		he2->next = he0;
		he2->origin = v2;
		he2->face = face;

		// set face member data
		face->halfEdge = he0;

		// associate vertices with half edges
		if (!v0->halfEdge)
		{
			v0->halfEdge = he0;
		}
		if (!v1->halfEdge)
		{
			v1->halfEdge = he1;
		}
		if (!v2->halfEdge)
		{
			v2->halfEdge = he2;
		}
	}

	assert(vertexMap.size() == _indexedMesh.vertices.size());
	assert(faces.size() == _indexedMesh.indices.size() / 3);

	// copy half edges and vertices into vector members
	for (auto &item : halfEdgeMap)
	{
		auto it = halfEdgeMap.find({ item.first.second, item.first.first });
		item.second->twin = (it != halfEdgeMap.end()) ? it->second : nullptr;
		halfEdges.push_back(item.second);
	}
	for (auto &item : vertexMap)
	{
		assert(item.second);
		vertices.push_back(item.second);
	}

#ifdef _DEBUG
	std::set<uint32_t> indexSet(_indexedMesh.indices.begin(), _indexedMesh.indices.end());
	assert(indexSet.size() == vertices.size());
#endif
}

HalfEdgeMesh::~HalfEdgeMesh()
{
	for (auto vertex : vertices)
	{
		delete vertex;
	}

	for (auto face : faces)
	{
		delete face;
	}

	for (auto halfEdge : halfEdges)
	{
		delete halfEdge;
	}
}
