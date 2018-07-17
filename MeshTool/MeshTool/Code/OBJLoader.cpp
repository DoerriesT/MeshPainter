#include "OBJLoader.h"
#include <string>
#include <fstream>
#include <cassert>
#include <map>
#include "Utility.h"

IndexedMesh OBJLoader::loadOBJ(const char *_filepath)
{
	uint32_t currentIndex = 0;
	std::map<std::string, uint32_t> vertexToIndexMap;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	// parse file
	std::ifstream objFile(_filepath);
	bool objectFound = false;
	std::string line;
	while (std::getline(objFile, line))
	{
		// skip empty lines and comments
		if (line.empty() || line[0] == '#')
		{
			continue;
		}

		std::vector<std::string> lineParts = Utility::split(line, " ");
		assert(!lineParts.empty());

		// object
		if (lineParts[0] == "o")
		{
			// we only support one sub-mesh/object per file
			if (objectFound)
			{
				break;
			}
			objectFound = true;
		}
		else if (lineParts[0] == "v")
		{
			assert(lineParts.size() == 4);
			positions.push_back(glm::vec3(std::stof(lineParts[1]), std::stof(lineParts[2]), std::stof(lineParts[3])));
		}
		// normal
		else if (lineParts[0] == "vn")
		{
			assert(lineParts.size() == 4);
			normals.push_back(glm::vec3(std::stof(lineParts[1]), std::stof(lineParts[2]), std::stof(lineParts[3])));
		}
		// tex coord
		else if (lineParts[0] == "vt")
		{
			assert(lineParts.size() == 3);
			texCoords.push_back(glm::vec2(std::stof(lineParts[1]), std::stof(lineParts[2])));
		}
		// face
		else if (lineParts[0] == "f")
		{
			assert(lineParts.size() == 4);
			for (unsigned int i = 1; i < 4; ++i)
			{
				std::vector<std::string> faceParts = Utility::split(lineParts[i], "/");
				assert(faceParts.size() == 3);

				int posIndex = std::stoi(faceParts[0]);
				int texCoordIndex = std::stoi(faceParts[1]);
				int normalIndex = std::stoi(faceParts[2]);

				Vertex vertex;

				// position
				if (posIndex < 0)
				{
					assert(-posIndex <= positions.size());
					posIndex = positions.size() + posIndex;
				}
				else
				{
					--posIndex;
				}
				assert(posIndex >= 0 && posIndex < positions.size());
				vertex.position = positions[posIndex];

				// texcoord
				if (texCoordIndex < 0)
				{
					assert(-texCoordIndex <= texCoords.size());
					texCoordIndex = texCoords.size() + texCoordIndex;
				}
				else
				{
					--texCoordIndex;
				}
				assert(texCoordIndex >= 0 && texCoordIndex < texCoords.size());
				vertex.texCoord = texCoords[texCoordIndex];


				// normal
				if (normalIndex < 0)
				{
					assert(-normalIndex <= normals.size());
					normalIndex = normals.size() + normalIndex;
				}
				else
				{
					--normalIndex;
				}
				assert(normalIndex >= 0 && normalIndex < normals.size());
				vertex.normal = normals[normalIndex];

				std::string vertexStr = std::to_string(posIndex) + " " + std::to_string(texCoordIndex) + " " + std::to_string(normalIndex);

				auto it = vertexToIndexMap.find(vertexStr);
				if (it != vertexToIndexMap.end())
				{
					indices.push_back(it->second);
				}
				else
				{
					vertexToIndexMap[vertexStr] = currentIndex;
					indices.push_back(currentIndex);
					vertices.push_back(vertex);
					++currentIndex;
				}
			}
		}
	}

	assert(currentIndex == vertices.size());

	return { vertices, indices };
}
