#include "Mesh.h"
#include "leo_math.h"
#include <vector>
#include "OBJLoader.h"

using namespace graphics;

graphics::Mesh::Mesh(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib)
	:
	vertexArray(std::move(va)),
	vertexBuffer(std::move(vb)),
	indexBuffer(std::move(ib))
{
}

graphics::Mesh graphics::Mesh::Load(const char* filename)
{
	ObjMesh obj(filename);

	std::vector<float> vertex_buffer;

	for (auto& v : obj.vertices)
	{
		vertex_buffer.emplace_back(v.pos.x);
		vertex_buffer.emplace_back(v.pos.y);
		vertex_buffer.emplace_back(v.pos.z);

		vertex_buffer.emplace_back(v.texCord.s);
		vertex_buffer.emplace_back(v.texCord.t);

		vertex_buffer.emplace_back(v.normal.x);
		vertex_buffer.emplace_back(v.normal.y);
		vertex_buffer.emplace_back(v.normal.z);
	}

	VertexBuffer vertexBuffer((const void*)vertex_buffer.data(), vertex_buffer.size() * sizeof(float));

	graphics::ElementType arr[3] = { graphics::FLOAT3, graphics::FLOAT2, graphics::FLOAT3_N };
	graphics::Layout<3> layout(arr);

	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, layout);

	IndexBuffer indexBuffer(obj.indices.data(), obj.indices.size());

	return { vertexArray, vertexBuffer, indexBuffer };
}

graphics::Mesh graphics::Mesh::GenarateCube()
{
	float vertexs[] = {
		// pos                 // tex cord      // normal
		// Forward
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f,  0.0f, -1.0f, //0
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f,  0.0f, -1.0f, //1
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f,  0.0f, -1.0f, //2
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f,  0.0f, -1.0f, //3

		// EAST							  
		 0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    1.0f,  0.0f,  0.0f, //4
		 0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    1.0f,  0.0f,  0.0f, //5
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    1.0f,  0.0f,  0.0f, //6
		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    1.0f,  0.0f,  0.0f, //7

		// BACK							  
		 0.5f,  0.5f,  0.5f,     0.0f, 1.0f,    0.0f,  0.0f,  1.0f, //8
		 0.5f, -0.5f,  0.5f,     0.0f, 0.0f,    0.0f,  0.0f,  1.0f, //9
		-0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    0.0f,  0.0f,  1.0f, //10
		-0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    0.0f,  0.0f,  1.0f, //11

		// WEST							  
		-0.5f, -0.5f, -0.5f,     1.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //12
		-0.5f,  0.5f, -0.5f,     1.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //13
		-0.5f,  0.5f,  0.5f,     0.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //14
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //15

		// NORTH						  
		-0.5f,  0.5f, -0.5f,     0.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //16
		 0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //17
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //18
		-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //19

		// SOUTH						  
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    0.0f, -1.0f,  0.0f,   //20
		 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   //21
		 0.5f, -0.5f,  0.5f,     1.0f, 1.0f,    0.0f, -1.0f,  0.0f,   //22
		-0.5f, -0.5f,  0.5f,     0.0f, 1.0f,    0.0f, -1.0f,  0.0f    //23
	};

	VertexBuffer vertexBuffer(vertexs, sizeof(vertexs));

	graphics::ElementType arr[3] = { graphics::FLOAT3, graphics::FLOAT2, graphics::FLOAT3_N };
	graphics::Layout<3> layout(arr);

	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, layout);

	// index buffer
	uint32_t indices[] = {
		// Forward
		0, 1, 2, /**/ 0, 2, 3,
		// EAST
		5, 4, 6, /**/ 5, 6, 7,
		// BACK
		9, 8, 10, /**/ 9, 10, 11,
		// WEST
		15, 14, 13, /**/ 15, 13, 12,
		// NORTH
		16, 19, 18, /**/ 16, 18, 17,
		// SOUTH
		22, 23, 20, /**/ 22, 20, 21
	};
	IndexBuffer indexBuffer(indices, 36);

	return { vertexArray, vertexBuffer, indexBuffer };
}

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCord;
	glm::vec3 normal;
};

float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

// Note latitude east west | longitude North to south
Mesh graphics::Mesh::GenarateSphere(uint32_t prec)
{
	const uint32_t numVertices = (prec + 1) * (prec + 1);
	const uint32_t numIndices = prec * prec * 6;

	std::vector<Vertex> vertices(numVertices);

	// calculate triangle vertices
	for (int i = 0; i <= prec; i++) {
		for (int j = 0; j <= prec; j++) {
			float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
			float x = -(float)cos(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			float z = (float)sin(toRadians(j * 360.0f / (float)(prec))) * (float)abs(cos(asin(y)));
			vertices[i * (prec + 1) + j].pos = glm::vec3(x, y, z);
			vertices[i * (prec + 1) + j].texCord = glm::vec2(((float)j / prec), ((float)i / prec));
			vertices[i * (prec + 1) + j].normal = glm::vec3(x, y, z);

		}
	}

	std::vector<uint32_t> indices(numIndices);
	
	// calculate triangle indices
	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
		}
	}

	std::vector<float> vertex_buffer;

	for (Vertex& v : vertices)
	{
		vertex_buffer.emplace_back(v.pos.x);
		vertex_buffer.emplace_back(v.pos.y);
		vertex_buffer.emplace_back(v.pos.z);

		vertex_buffer.emplace_back(v.texCord.s);
		vertex_buffer.emplace_back(v.texCord.t);

		vertex_buffer.emplace_back(v.normal.x);
		vertex_buffer.emplace_back(v.normal.y);
		vertex_buffer.emplace_back(v.normal.z);
	}

	VertexBuffer vertexBuffer((const void*)vertex_buffer.data(), vertex_buffer.size() * sizeof(float) );

	graphics::ElementType arr[3] = { graphics::FLOAT3, graphics::FLOAT2, graphics::FLOAT3_N };
	graphics::Layout<3> layout(arr);

	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, layout);


	IndexBuffer indexBuffer(indices.data(), indices.size());

	return { vertexArray, vertexBuffer, indexBuffer };
}


