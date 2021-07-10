#pragma once
#include <cinttypes>

namespace graphics
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(const uint32_t* data, uint32_t count);
		~IndexBuffer();

		void Recreare(const uint32_t* data, uint32_t count);

		void Bind() const;
		void UnBind() const;

		inline uint32_t GetCount() const { return m_count; }

	private:
		uint32_t m_id = 0;
		uint32_t m_count = 0;
	};
}



