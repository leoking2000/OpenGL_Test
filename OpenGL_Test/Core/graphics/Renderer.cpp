#include "Renderer.h"
#include "Platform/OpenGL.h"

using namespace graphics;

void graphics::Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void graphics::Renderer::Init()
{
}

void graphics::Renderer::SetClearColor(float r, float g, float b, float a)
{
	glCall(glClearColor(r, g, b, a));
}

void graphics::Renderer::Clear()
{
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}
