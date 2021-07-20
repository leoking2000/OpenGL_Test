#pragma once
#include "Colors.h"
#include "defines.h"

namespace graphics
{
	class Canvas
	{
	public:
		Canvas(uint32_t width, uint32_t height, const Color& clear_color);
		~Canvas();

		void Clear();
		void PutPixel(uint32_t x, uint32_t y, const Color& c);
		Color GetPixel(uint32_t x, uint32_t y);
		void DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, const Color& c);
		uint32_t GetWidth();
		uint32_t GetHeight();

		bool Depth_TestSet(uint32_t x, uint32_t y, float z);

		void SetClearColor(const Color& clear_color);


		Color* __GetData();
	private:
		Color m_clear_color;

		uint32_t m_width;
		uint32_t m_height;

		Color* m_data = nullptr;
		float* z_buffer = nullptr;
	};
}


