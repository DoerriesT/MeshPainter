#pragma once
#include "Mesh.h"

namespace OBJLoader
{
	enum class Error
	{
		SUCCESS, FAILURE
	};

	IndexedMesh loadOBJ(const char *_filepath, Error &_error);
}
