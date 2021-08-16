#include "MatOneColor.h"
#include "Core/graphics/Renderer.h"
#include "../imgui/imgui.h"

graphics::MatOneColor::MatOneColor(const glm::vec3 color)
	:
	color(color)
{
}

void graphics::MatOneColor::SetUniforms(const glm::mat4 model)
{
	Renderer::OneColorShader().Bind();

	Renderer::BasicShader().SetUniform("proj", graphics::Renderer::Proj());
	Renderer::BasicShader().SetUniform("view", graphics::Renderer::MainCamera().GetCameraView());
	Renderer::BasicShader().SetUniform("model", model);

	Renderer::BasicShader().SetUniform("mat.color", color.r, color.g, color.b);
}

void graphics::MatOneColor::Imgui(const char* name)
{
	ImGui::Begin(name);

	ImGui::ColorEdit3("Color", glm::value_ptr(color));

	ImGui::End();
}
