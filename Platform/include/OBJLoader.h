#pragma once
#include <vector>
#include "leo_math.h"

namespace OBJLoader
{
	class ObjMesh
	{
	public:
		struct Vertex
		{
			glm::vec3 pos;
			glm::vec2 texCord;
			glm::vec3 normal;

			bool operator==(const Vertex& rhs)
			{
				return pos     == rhs.pos     && 
					   texCord == rhs.texCord && 
					   normal  == rhs.normal;
			}
		};
	public:
		ObjMesh(const char* filename);

		void load(const char* filename);
	public:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}

