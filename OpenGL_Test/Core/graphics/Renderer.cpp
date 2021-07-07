#include "Renderer.h"
#include "Platform/OpenGL.h"

using namespace graphics;

void graphics::Renderer::Draw(const VartexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	glCall(glClear(GL_COLOR_BUFFER_BIT));

	va.Bind();
	ib.Bind();
	shader.Bind();

	glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void graphics::Renderer::SetClearColor(float r, float g, float b, float a)
{
	glCall(glClearColor(r, g, b, a));
}
