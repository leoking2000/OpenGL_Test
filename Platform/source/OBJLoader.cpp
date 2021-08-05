#include "OBJLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Log.h"

OBJLoader::ObjMesh::ObjMesh(const char* filename)
{
	load(filename);
}

void OBJLoader::ObjMesh::load(const char* filename)
{
	vertices.clear();
	indices.clear();

	assert(filename != nullptr);

	std::ifstream file(filename, std::ios::in);

	assert(file.fail() == false);

	std::vector<glm::vec3> posisitions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	std::string line;

	while (!file.eof())
	{
		std::getline(file, line);

		if (line.compare(0, 2, "v ") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			glm::vec3 v;
			ss >> v.x;
			ss >> v.y;
			ss >> v.z;
			posisitions.push_back(v);

		}
		else if (line.compare(0, 2, "vt") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			glm::vec2 v;
			ss >> v.x;
			ss >> v.y;
			texCoords.push_back(v);
		}
		else if (line.compare(0, 2, "vn") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			glm::vec3 v;
			ss >> v.x;
			ss >> v.y;
			ss >> v.z;
			normals.push_back(v);
		}
		else if (line.compare(0, 2, "f ") == 0)
		{
			std::stringstream ss(line.erase(0, 2));

			Vertex v[3];
			for (int i = 0; i < 3; i++)
			{
				std::string vertex_str;
				std::getline(ss, vertex_str, ' ');

				std::string p_index;
				std::string t_index;
				std::string n_index;

				std::stringstream vertexSS(vertex_str);
				std::getline(vertexSS, p_index, '/');
				std::getline(vertexSS, t_index, '/');
				std::getline(vertexSS, n_index, '/');

				if (t_index.length() == 0)
				{
					v[i] = { posisitions[stoi(p_index) - 1], { 0.0f, 0.0f }, normals[stoi(n_index) - 1] };
				}
				else
				{
					v[i] = { posisitions[stoi(p_index) - 1], texCoords[stoi(t_index) - 1], normals[stoi(n_index) - 1] };
				}
				
			}

			for (int i = 0; i < 3; i++)
			{
				auto v_index = std::find(vertices.begin(), vertices.end(), v[i]);

				if (v_index == std::end(vertices) || vertices.size() == 0)
				{
					// fist time we see this vertex
					Vertex newVertex = v[i];
					vertices.push_back(newVertex);
					indices.push_back(vertices.size() - 1);
				}
				else
				{
					// we have seen this vertex before
					uint32_t index = v_index - vertices.begin();
					indices.push_back(index);
				}

			}

		}

	}

	assert(vertices.size() != 0);

	file.close();

	std::string msg(filename);
	msg += " Has been Loaded!!!";
	Logger::LogInfo(msg.c_str());
}
