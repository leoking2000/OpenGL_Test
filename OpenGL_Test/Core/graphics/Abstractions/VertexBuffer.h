#pragma once
#include <cinttypes>

namespace graphics
{

	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(const void* data, uint32_t size);
		~VertexBuffer();

		void Recreate(const void* data, uint32_t size);

		void Bind() const;
		void UnBind() const;

	private:
		uint32_t m_id;

	};

}