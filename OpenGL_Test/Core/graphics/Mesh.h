#pragma once
#include "Core/graphics/Abstractions/VertexArray.h"
#include "Core/graphics/Abstractions/IndexBuffer.h"

namespace graphics
{
	class Mesh
	{
	public:
		Mesh(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib);

		static Mesh GenarateCube();
		static Mesh GenarateSphere(uint32_t prec = 48);
		static Mesh Load(const char* filename);

	public:
		void Bind() const
		{
			vertexArray.Bind();		
			indexBuffer.Bind();
		}

	public:
		VertexArray vertexArray;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};
}