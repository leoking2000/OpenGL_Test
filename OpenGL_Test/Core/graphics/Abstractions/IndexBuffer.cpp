#include "IndexBuffer.h"
#include "OpenGL.h"

using namespace graphics;

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
	:
	m_count(count)
{
	glCall(glGenBuffers(1, &m_id));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), (const void*)data, GL_STATIC_DRAW));
}

graphics::IndexBuffer::IndexBuffer(IndexBuffer&& other)
	:
	m_count(other.m_count),
	m_id(other.m_id)
{
	other.m_count = 0;
	other.m_id = 0;
}

IndexBuffer& graphics::IndexBuffer::operator=(IndexBuffer&& other)
{
	glCall(glDeleteBuffers(1, &m_id));

	m_count = other.m_count;
	m_id = other.m_id;

	other.m_count = 0;
	other.m_id = 0;

	return *this;
}

IndexBuffer::~IndexBuffer()
{
	glCall(glDeleteBuffers(1, &m_id));
}

void graphics::IndexBuffer::Recreare(const uint32_t* data, uint32_t count)
{
	glCall(glDeleteBuffers(1, &m_id));

	m_count = count;

	glCall(glGenBuffers(1, &m_id));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), (const void*)data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::UnBind() const
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
