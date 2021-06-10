#include "Texture.h"
#include <stb/stb_image.h>
#include <assert.h>

graphics::Texture::Texture(const char* file_name)
{
	Load(file_name);
}

graphics::Texture::~Texture()
{
	delete m_data;
}

int graphics::Texture::GetWidth() const
{
	return m_width;
}

int graphics::Texture::GetHeight() const
{
	return m_height;
}

void graphics::Texture::Load(const char* file_name)
{
	delete m_data;
	m_data = stbi_load(file_name, &m_width, &m_height, &m_bpp, 0);
	assert(m_data);
}

//void graphics::Texture::PutPixel(int x, int y, const graphics::Color& c)
//{
//	//m_data[y * m_width + x] = c;
//}

graphics::Color graphics::Texture::GetPixel(int x, int y) const
{
	int p = (y * m_width + x) * m_bpp;

	return { m_data[p], m_data[p + 1], m_data[p + 2] };
}


