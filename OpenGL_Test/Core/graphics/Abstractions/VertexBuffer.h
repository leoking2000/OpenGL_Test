#pragma once
#include <cinttypes>

namespace graphics
{

	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, uint32_t size);

		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer& operator=(const VertexBuffer) = delete;

		VertexBuffer(VertexBuffer&& other);
		VertexBuffer& operator=(VertexBuffer&& other);

		~VertexBuffer();

		void Recreate(const void* data, uint32_t size);

		void Bind() const;
		void UnBind() const;

	private:
		uint32_t m_id;

	};

}