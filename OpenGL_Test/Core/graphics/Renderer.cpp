#include "Renderer.h"
#include "Platform/OpenGL.h"
#include "Platform/MainWindow.h"

using namespace graphics;

glm::mat4 graphics::Renderer::proj;

void graphics::Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void graphics::Renderer::Init()
{
	glCall(glEnable(GL_DEPTH_TEST));

	proj = glm::perspective(glm::radians(45.0f), (float)Core::GetWidth() / (float)Core::GetHeight(), 0.1f, 500.0f);
}

void graphics::Renderer::SetClearColor(float r, float g, float b, float a)
{
	glCall(glClearColor(r, g, b, a));
}

void graphics::Renderer::Clear()
{
	glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
