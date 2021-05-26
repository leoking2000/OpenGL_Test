#include "Texture.h"
#include <stb/stb_image.h>
#include <assert.h>

Texture::Texture(const char* file_name)
{
	Load(file_name);
}

Texture::~Texture()
{
	delete m_data;
}

int Texture::GetWidth() const
{
	return m_width;
}

int Texture::GetHeight() const
{
	return m_height;
}

void Texture::Load(const char* file_name)
{
	m_data = stbi_load(file_name, &m_width, &m_height, &m_bpp, 4);
	assert(m_data);
}

//void Texture::PutPixel(int x, int y, const graphics::Color& c)
//{
//	//m_data[y * m_width + x] = c;
//}

graphics::Color Texture::GetPixel(int x, int y) const
{
	int p = (y * m_width + x) * m_bpp;

	return { m_data[p], m_data[p + 1], m_data[p + 2] };
}

graphics::Color* Texture::__GetData()
{
	return nullptr;
}
