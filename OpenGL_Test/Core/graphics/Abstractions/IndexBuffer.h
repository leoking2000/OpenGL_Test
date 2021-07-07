#pragma once
#include <cinttypes>

namespace graphics
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const uint32_t* data, uint32_t count);
		~IndexBuffer();

		void Bind() const;
		void UnBind() const;

		inline uint32_t GetCount() const { return m_count; }

	private:
		uint32_t m_id;
		uint32_t m_count;
	};
}



