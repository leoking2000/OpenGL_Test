#include "IndexBuffer.h"
#include "Platform/OpenGL.h"

using namespace graphics;

graphics::IndexBuffer::IndexBuffer()
{
}

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
	:
	m_count(count)
{
	glCall(glGenBuffers(1, &m_id));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), (const void*)data, GL_STATIC_DRAW));
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