#pragma once
#include <cinttypes>

#define WIDTH 900
#define HEIGHT 900

namespace graphics
{
	struct Color
	{
		uint8_t r, g, b;
	};

	class Canvas
	{
	public:
		Canvas(uint32_t width, uint32_t height, const Color& clear_color);
		~Canvas();

		void Clear();
		void PutPixel(uint32_t x, uint32_t y, const Color& c);
		Color GetPixel(uint32_t x, uint32_t y);
		void DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, const Color& c);
		uint32_t GetWidth();
		uint32_t GetHeight();

		void SetClearColor(const Color& clear_color);


		Color* __GetData();
	private:
		Color m_clear_color;

		uint32_t m_width;
		uint32_t m_height;

		Color* m_data = nullptr;
	};
}


