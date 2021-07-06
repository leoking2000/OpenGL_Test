#pragma once
#include <cinttypes>
#include <assert.h>

namespace graphics
{
	enum ElementType
	{
		FLOAT2 = 0,
		FLOAT2_N = 1,

		FLOAT3 = 2,
		FLOAT3_N = 3,

		FLOAT4 = 4,
		FLOAT4_N = 5,

		UCHAR3 = 6,
		UCHAR3_N = 7,

		UCHAR4 = 8,
		UCHAR4_N = 9
	};

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
}

