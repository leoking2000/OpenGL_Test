#include "Renderer.h"
#include "OpenGL.h"
#include "MainWindow.h"

using namespace graphics;

Renderer* Renderer::instance = nullptr;

graphics::Renderer::Renderer()
	:
	light(glm::vec3(0.0f), glm::vec3(1.0f))
{
}

void graphics::Renderer::Init()
{
	glCall(glEnable(GL_DEPTH_TEST));

	Get().proj = glm::perspective(glm::radians(45.0f), (float)Platform::GetWidth() / (float)Platform::GetHeight(), 0.1f, 500.0f);

	Get().basicShader.Recreate("Shaders/Basic.glsl");
	Get().oneColorShader.Recreate("Shaders/OneColor.glsl");
}

void graphics::Renderer::CleanUp()
{
	delete instance;
}

graphics::Renderer& graphics::Renderer::Get()
{
	if (!instance)
	{
		instance = new Renderer();
	}

	return *instance;
}

void graphics::Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void graphics::Renderer::Draw(const Matirial* mat, const Mesh& mesh)
{
	mesh.Bind();

	glCall(glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}



Camera& graphics::Renderer::MainCamera()
{
	return Get().cam;
}

glm::mat4 graphics::Renderer::Proj()
{
	return Get().proj;
}

Shader& graphics::Renderer::BasicShader()
{
	return Get().basicShader;
}

Shader& graphics::Renderer::OneColorShader()
{
	return Get().oneColorShader;
}

PointLight& graphics::Renderer::MainLight()
{
	return Get().light;
}

void graphics::Renderer::SetClearColor(float r, float g, float b, float a)
{
	glCall(glClearColor(r, g, b, a));
}

void graphics::Renderer::Clear()
{
	glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
