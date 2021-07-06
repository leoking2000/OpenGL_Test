#include "VartexArray.h"
#include "Platform/OpenGL.h"
#include "Core/utilities/Log.h"
#include <assert.h>

using namespace graphics;

graphics::VartexArray::VartexArray()
{
	glCall(glGenVertexArrays(1, &m_id));
	glCall(glBindVertexArray(m_id));
}

graphics::VartexArray::~VartexArray()
{
	glCall(glDeleteVertexArrays(1, &m_id));
}

void graphics::VartexArray::Bind() const
{
	glCall(glBindVertexArray(m_id));
}

void graphics::VartexArray::UnBind() const
{
	glCall(glBindVertexArray(0));
}

void graphics::VartexArray::AddAttrib(uint32_t i, ElementType element_type, uint32_t stride, uint32_t& offset)
{
	auto normalize = element_type % 2 == 0 ? GL_FALSE : GL_TRUE;
	auto type = GL_FLOAT;
	uint32_t size = sizeof(float);
	uint32_t count = 1;

	switch (element_type)
	{
	case FLOAT2:
	case FLOAT2_N:
		type = GL_FLOAT;
		size = sizeof(float);
		count = 2;
		break;
	case FLOAT3:
	case FLOAT3_N:
		type = GL_FLOAT;
		size = sizeof(float);
		count = 3;
		break;
	case FLOAT4:
	case FLOAT4_N:
		type = GL_FLOAT;
		size = sizeof(float);
		count = 4;
		break;

	case UCHAR3:
	case UCHAR3_N:
		type = GL_UNSIGNED_BYTE;
		size = 1;
		count = 3;
		break;
	case UCHAR4:
	case UCHAR4_N:
		type = GL_UNSIGNED_BYTE;
		size = 1;
		count = 4;
		break;
	default:
		Logger::LogError("VartexArray::AddBuffer error unknowed ElementType!!!");
		assert(false);
		break;
	}

	glCall(glEnableVertexAttribArray(i));
	glCall(glVertexAttribPointer(i, count, type, normalize, stride, (const void*)offset));

	offset += count * size;
}

