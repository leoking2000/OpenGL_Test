#include "Texture.h"
#include <assert.h>
#include "stb/stb_image.h"
#include "OpenGL.h"

using namespace graphics;

graphics::Texture::Texture(uint32_t width, uint32_t height)
	:
	m_width(width), m_height(height), m_data(new Color[width * height])
{
	Clear(Colors::Black);
	UploadToGPU();

	m_name = std::to_string(m_id);
}

graphics::Texture::Texture(uint32_t width, uint32_t height, const Color& c)
	:
	m_width(width), m_height(height), m_data(new Color[width * height])
{
	Clear(c);
	UploadToGPU();

	m_name = std::to_string(m_id);
}

graphics::Texture::Texture(const char* file_name)
	:
	m_name(file_name)
{
	Load(file_name);
	UploadToGPU();
}

graphics::Texture::Texture(Texture&& other)
	:
	m_width(other.m_width),
	m_height(other.m_height),
	m_data(other.m_data),
	m_id(other.m_id),
	m_name(std::move(other.m_name))
{
	other.m_width = 0;
	other.m_height = 0;
	other.m_id = 0;
	other.m_data = nullptr;
}

Texture& graphics::Texture::operator=(Texture&& other)
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_data = other.m_data;
	m_id = other.m_id;
	m_name = std::move(other.m_name);

	other.m_width = 0;
	other.m_height = 0;
	other.m_id = 0;
	other.m_data = nullptr;

	return *this;
}

graphics::Texture::~Texture()
{
    delete[] m_data;
	glCall(glDeleteTextures(1, &m_id));
}

void graphics::Texture::Load(const char* file_name)
{
	stbi_set_flip_vertically_on_load(1);

	int width;
	int height;
	int bpp;

	Color* data = (Color*)stbi_load(file_name, &width, &height, &bpp, 4);

	if (data != nullptr)
	{
		delete[] m_data;

		m_width = width;
		m_height = height;

		m_data = data;

		glCall(glDeleteTextures(1, &m_id));
		UploadToGPU();

		m_name = file_name;
	}

}

void graphics::Texture::Clear(const Color& c)
{
	for (uint32_t y = 0; y < m_height; y++)
	{
		for (uint32_t x = 0; x < m_width; x++)
		{
			m_data[y * m_width + x] = c;
		}
	}
}

void graphics::Texture::PutPixel(int x, int y, const graphics::Color& c)
{
	m_data[y * m_width + x] = c;
}

graphics::Color graphics::Texture::GetPixel(int x, int y) const
{
    return m_data[y * m_width + x];
}

void graphics::Texture::Bind(uint32_t slot) const
{
	glCall(glActiveTexture(GL_TEXTURE0 + slot));
	glCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void graphics::Texture::UnBind() const
{
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void graphics::Texture::UpdateGPUData()
{
	glCall(glBindTexture(GL_TEXTURE_2D, m_id));
	glCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_data));

}

void graphics::Texture::UploadToGPU()
{
	glCall(glGenTextures(1, &m_id));
	glCall(glBindTexture(GL_TEXTURE_2D, m_id));

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
