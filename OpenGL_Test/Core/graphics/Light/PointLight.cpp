#include "PointLight.h"
#include "Core/graphics/Renderer.h"
#include "../imgui/imgui.h"

graphics::PointLight::PointLight(const glm::vec3& pos, const glm::vec3& color)
	:
	pos(pos),
	color(color),
	mesh(graphics::Mesh::GenarateSphere(24))
{
}

void graphics::PointLight::Draw()
{
	glm::mat4 model(1.0f);

	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(0.1f));

	//Renderer::OneColorShader().Bind();

	Renderer::OneColorShader().SetUniform("proj", graphics::Renderer::Proj());
	Renderer::OneColorShader().SetUniform("view", graphics::Renderer::MainCamera().GetCameraView());
	Renderer::OneColorShader().SetUniform("model", model);

	Renderer::OneColorShader().SetUniform("matColor", color.r, color.g, color.b);

	Renderer::Draw(mesh->vertexArray, mesh->indexBuffer, Renderer::OneColorShader());

}

void graphics::PointLight::Imgui(const char* name)
{
	ImGui::Begin(name);

	ImGui::SliderFloat3("Light pos", glm::value_ptr(pos), -100.0f, 100.0f);
	ImGui::ColorEdit3("Light Color", glm::value_ptr(color));

	ImGui::End();
}

