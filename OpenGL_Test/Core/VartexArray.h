#pragma once
#include "utilities.h"
#include "VertexBuffer.h"

class VartexArray
{
public:
	enum ElementType
	{
		FLOAT2      = 0,
		FLOAT2_N    = 1,

		FLOAT3      = 2,
		FLOAT3_N    = 3,

		FLOAT4      = 4,
		FLOAT4_N    = 5,

		UCHAR3      = 6,
		UCHAR3_N    = 7,

		UCHAR4      = 8,
		UCHAR4_N    = 9
	};
public:
	template<uint32_t ELEMENTS_COUNT>
	class Layout
	{
	public:
		Layout(ElementType* arr)
		{
			assert(arr != nullptr);
			m_stride = 0;

			for (uint32_t i = 0; i < ELEMENTS_COUNT; i++)
			{
				m_arr[i] = arr[i];

				switch (m_arr[i])
				{
					case FLOAT2:
					case FLOAT2_N:
						m_stride += 2 * sizeof(float);
						break;
					case FLOAT3:
					case FLOAT3_N:
						m_stride += 3 * sizeof(float);
						break;
					case FLOAT4:
					case FLOAT4_N:
						m_stride += 4 * sizeof(float);
						break;

					case UCHAR3:
					case UCHAR3_N:
						m_stride += 3 * sizeof(char);
						break;
					case UCHAR4:
					case UCHAR4_N:
						m_stride += 4 * sizeof(char);
						break;
				default:
					assert(false);
					break;
				}
			}
		}

		ElementType operator[](int i) const
		{
			return m_arr[i];
		}

		inline uint32_t GetStride() const
		{
			return m_stride;
		}

		inline uint32_t GetCount() const { return ELEMENTS_COUNT; }

	private:
		ElementType m_arr[ELEMENTS_COUNT];
		uint32_t m_stride;
	};
public:
	VartexArray()
	{
		glCall(glGenVertexArrays(1, &m_id));
		glCall(glBindVertexArray(m_id));
	}
	~VartexArray()
	{
		glCall(glDeleteVertexArrays(1, &m_id));
	}

	void Bind() const
	{
		glCall(glBindVertexArray(m_id));
	}

	void UnBind() const
	{
		glCall(glBindVertexArray(0));
	}

	template<uint32_t ELEMENTS_COUNT>
	void AddBuffer(const VertexBuffer& vb, const Layout<ELEMENTS_COUNT>& layout)
	{
		Bind();
		vb.Bind();

		uint32_t offset = 0;

		for (uint32_t i = 0; i < ELEMENTS_COUNT; i++)
		{
			ElementType t = layout[i];
			auto normalize = t % 2 == 0 ? GL_FALSE : GL_TRUE;
			auto type = GL_FLOAT;
			uint32_t size = sizeof(float);
			uint32_t count = 1;

			switch (layout[i])
			{
			case FLOAT2:
			case FLOAT2_N:
				type = GL_FLOAT;
				size = sizeof(float);
				count = 2;
				break;
			case FLOAT3:
			case FLOAT3_N:
				type = GL_FLOAT;
				size = sizeof(float);
				count = 3;
				break;
			case FLOAT4:
			case FLOAT4_N:
				type = GL_FLOAT;
				size = sizeof(float);
				count = 4;
				break;

			case UCHAR3:
			case UCHAR3_N:
				type = GL_UNSIGNED_BYTE;
				size = sizeof(char);
				count = 3;
				break;
			case UCHAR4:
			case UCHAR4_N:
				type = GL_UNSIGNED_BYTE;
				size = sizeof(char);
				count = 4;
				break;
			default:
				assert(false);
				break;
			}

			glCall(glEnableVertexAttribArray(i));
			glCall(glVertexAttribPointer(i, count, type, normalize, layout.GetStride(), (const void*)offset));

			offset += count * size;

		}
	}

private:
	uint32_t m_id;
};

