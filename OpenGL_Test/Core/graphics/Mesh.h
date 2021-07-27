#pragma once
#include "Core/graphics/Abstractions/VertexArray.h"
#include "Core/graphics/Abstractions/IndexBuffer.h"

namespace graphics
{
	class Mesh
	{
	public:

		static Mesh* GenarateCube();

		static Mesh* GenarateSphere(uint32_t prec = 48);

		void Bind() const
		{
			vertexArray.Bind();		
			indexBuffer.Bind();
		}

	public:
		graphics::VertexArray vertexArray;
		graphics::VertexBuffer vertexBuffer;
		graphics::IndexBuffer indexBuffer;
	public:
		Mesh() {};
	};
}