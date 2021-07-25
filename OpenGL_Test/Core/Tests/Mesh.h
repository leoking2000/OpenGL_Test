#pragma once
#include "Core/graphics/Abstractions/VertexArray.h"
#include "Core/graphics/Abstractions/IndexBuffer.h"

namespace Core
{
	class Mesh
	{
	public:

		static Mesh* GenarateCube()
		{
			Mesh* mesh = new Mesh();

			mesh->vertexArray = new graphics::VertexArray();
			mesh->vertexArray->Bind();

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

			mesh->vertexBuffer = new graphics::VertexBuffer(vertexs, sizeof(vertexs));

			graphics::ElementType arr[3] = { graphics::FLOAT3, graphics::FLOAT2, graphics::FLOAT3_N };
			graphics::Layout<3> layout(arr);
			mesh->vertexArray->AddBuffer(*mesh->vertexBuffer, layout);

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
			mesh->indexBuffer = new graphics::IndexBuffer(indices, 36);

			return mesh;
		}

		//static void GenaratePyramid()
		//{

		//}

		void Bind() const
		{
			vertexArray->Bind();		
			indexBuffer->Bind();
		}

		~Mesh()
		{
			delete vertexArray;
			delete vertexBuffer;
			delete indexBuffer;
		}

	public:
		graphics::VertexArray* vertexArray;
		graphics::VertexBuffer* vertexBuffer;
		graphics::IndexBuffer* indexBuffer;
	private:
		Mesh() {};
	};
}