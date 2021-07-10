#pragma once
#include "VertexBuffer.h"
#include "Layout.h"

namespace graphics {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void UnBind() const;

		template<uint32_t ELEMENTS_COUNT>
		void AddBuffer(const VertexBuffer& vb, const Layout<ELEMENTS_COUNT>& layout)
		{
			Bind();
			vb.Bind();

			uint32_t offset = 0;

			for (uint32_t i = 0; i < ELEMENTS_COUNT; i++)
			{
				AddAttrib(i, layout[i], layout.GetStride(), offset);
			}
		}

	private:
		void AddAttrib(uint32_t i ,ElementType element_type, uint32_t stride , uint32_t& offset);

	private:
		uint32_t m_id;
	};

}