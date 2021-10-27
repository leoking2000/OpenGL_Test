#include "MatBasic.h"
#include "Core/graphics/Renderer.h"
#include "../imgui/imgui.h"

using namespace graphics;

graphics::MatBasic::MatBasic(float red, float green, float blue)
	:
	color(red, green, blue),
	ambient(0.1f),
	diffuse(0.9f),
	specular(0.9f),
	shininess(200.0f)
{
}

graphics::MatBasic::MatBasic(const glm::vec3& color)
	:
	color(color),
	ambient(0.1f),
	diffuse(0.9f),
	specular(0.9f),
	shininess(200.0f)
{
}

graphics::MatBasic::MatBasic(const glm::vec3& color, float ambient, float diffuse, float specular, float shininess)
	:
	color(color),
	ambient(specular),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess)
{
}

void graphics::MatBasic::SetUniforms(const glm::mat4 model)
{
	Renderer::BasicShader().Bind();

	Renderer::BasicShader().SetUniform("proj", graphics::Renderer::Proj());
	Renderer::BasicShader().SetUniform("view", graphics::Renderer::MainCamera().GetCameraView());
	Renderer::BasicShader().SetUniform("model", model);

	glm::vec3 light_pos = Renderer::MainLight().pos;
	glm::vec3 light_color = Renderer::MainLight().color;

	Renderer::BasicShader().SetUniform("u_light_color", light_color.r, light_color.g, light_color.b);
	Renderer::BasicShader().SetUniform("u_light_pos", light_pos.r, light_pos.g, light_pos.b);

	Renderer::BasicShader().SetUniform("mat.ambient",   ambient * color.r,  ambient * color.g,  ambient * color.b);
	Renderer::BasicShader().SetUniform("mat.diffuse",   diffuse * color.r,  diffuse * color.g,  diffuse * color.b);
	Renderer::BasicShader().SetUniform("mat.specular", specular * color.r, specular * color.g, specular * color.b);
	Renderer::BasicShader().SetUniform("mat.shininess", shininess);
}

void graphics::MatBasic::Imgui(const char * name)
{
	ImGui::Begin(name);

	ImGui::ColorEdit3("Color", glm::value_ptr(color));

	ImGui::End();
}
