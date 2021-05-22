#include "Canvas.h"
#include <assert.h>
#include <algorithm>
#include <utility>

graphics::Canvas::Canvas(uint32_t width, uint32_t height, const Color& clear_color)
	:
	m_clear_color(clear_color),
	m_width(width),
	m_height(height),
	m_data(new Color[width * height])
{
	assert(m_width != 0);
	assert(m_height != 0);

	Clear();
}

graphics::Canvas::~Canvas()
{
	delete m_data;
}

void graphics::Canvas::Clear()
{
	for (uint32_t y = 0; y < m_height; y++)
	{
		for (uint32_t x = 0; x < m_width; x++)
		{
			PutPixel(x, y, m_clear_color);
		}
	}
}

void graphics::Canvas::PutPixel(uint32_t x, uint32_t y, const Color& c)
{
	assert(x < m_width);
	assert(y < m_height);

	m_data[y * m_width + x] = c;
}

graphics::Color graphics::Canvas::GetPixel(uint32_t x, uint32_t y)
{
	assert(x < m_width);
	assert(y < m_height);

	return m_data[y * m_width + x];
}

void graphics::Canvas::DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, const Color& c)
{
	const float dy = (float)y1 - (float)y0;
	const float dx = (float)x1 - (float)x0;
	const float steps = std::max(std::abs(dy), std::abs(dx));

	float x_inclese = dx / steps;
	float y_inclese = dy / steps;

	float x = (float)x0;
	float y = (float)y0;

	for (int i = 0; i < steps; ++i)
	{
		x += x_inclese;
		y += y_inclese;

		if (x >= 0 && x < WIDTH && y >= 0 && y < WIDTH)
		{
			PutPixel((uint32_t)x, (uint32_t)y, c);
		}	
	}
}

graphics::Color* graphics::Canvas::__GetData()
{
	return m_data;
}

uint32_t graphics::Canvas::GetWidth()
{
	return m_width;
}

uint32_t graphics::Canvas::GetHeight()
{
	return m_height;
}

void graphics::Canvas::SetClearColor(const Color& clear_color)
{
	m_clear_color = clear_color;
}
