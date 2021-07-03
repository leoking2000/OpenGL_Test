#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	glCall(glGenBuffers(1, &m_id));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void VertexBuffer::UnBind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	glCall(glDeleteBuffers(1, &m_id));
}
