#include "OBJLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Log.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ObjMesh::ObjMesh(const char* filename)
{
	load(filename);
}

void ObjMesh::load(const char* filename)
{
	assert(filename != nullptr);

	Assimp::Importer imp;
	const aiScene* model = imp.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices); 
	if (model == nullptr)
	{
		std::string msg(filename);
		msg += " Failed Loading";
		Logger::LogInfo(msg.c_str());
		return;
	}

	vertices.clear();
	indices.clear();

	for (uint32_t i = 0; i < model->mNumMeshes; i++)
	{
		const aiMesh* mesh = model->mMeshes[i];

		uint32_t offset = vertices.size();

		for (uint32_t v = 0; v < mesh->mNumVertices; v++)
		{
			ObjMesh::Vertex vert;

			vert.pos = glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);

			if (mesh->mTextureCoords[0] != nullptr)
			{
				vert.texCord = glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
			}
			else
			{
				vert.texCord = glm::vec2(0.0f, 0.0f);
			}
			
			vert.normal = glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);

			this->vertices.push_back(vert);
		}

		for (uint32_t f = 0; f < mesh->mNumFaces; f++)
		{
			const aiFace& face = mesh->mFaces[f];
			assert(face.mNumIndices == 3);

			indices.push_back(face.mIndices[0] + offset);
			indices.push_back(face.mIndices[1] + offset);
			indices.push_back(face.mIndices[2] + offset);
		}
	}

	std::string msg(filename);
	msg += " Has been Loaded!!!";
	Logger::LogInfo(msg.c_str());
}
