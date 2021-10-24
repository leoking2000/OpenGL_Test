#include "VertexBuffer.h"
#include "OpenGL.h"

using namespace graphics;

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	glCall(glGenBuffers(1, &m_id));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

graphics::VertexBuffer::VertexBuffer(VertexBuffer&& other)
	:
	m_id(other.m_id)
{
	other.m_id = 0;
}

VertexBuffer& graphics::VertexBuffer::operator=(VertexBuffer&& other)
{
	m_id = other.m_id;
	other.m_id = 0;
}

VertexBuffer::~VertexBuffer()
{
	glCall(glDeleteBuffers(1, &m_id));
}

void VertexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void VertexBuffer::UnBind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void graphics::VertexBuffer::Recreate(const void* data, uint32_t size)
{
	glCall(glDeleteBuffers(1, &m_id));

	glCall(glGenBuffers(1, &m_id));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}
