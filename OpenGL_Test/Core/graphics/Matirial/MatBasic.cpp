#include "MatBasic.h"
#include "Core/graphics/Renderer.h"
#include "../imgui/imgui.h"

using namespace graphics;

graphics::MatBasic::MatBasic(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
	:
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess),
	tex(1,1,Colors::White)
{
}

graphics::MatBasic::MatBasic(const char* tex)
	:
	ambient(0.1f, 0.1f, 0.1f),
	diffuse(1.0f, 1.0f, 1.0f),
	specular(0.5f, 0.5f, 0.5f),
	shininess(64.0f),
	tex(tex)
{
}

void graphics::MatBasic::SetUniforms(const glm::mat4 model)
{
	Renderer::BasicShader().Bind();
	tex.Bind(0);

	Renderer::BasicShader().SetUniform("proj", graphics::Renderer::Proj());
	Renderer::BasicShader().SetUniform("view", graphics::Renderer::MainCamera().GetCameraView());
	Renderer::BasicShader().SetUniform("model", model);

	Renderer::BasicShader().SetUniform("u_Tex", 0);

	glm::vec3 light_pos = Renderer::MainLight().pos;
	glm::vec3 light_color = Renderer::MainLight().color;

	Renderer::BasicShader().SetUniform("u_light_color", light_color.r, light_color.g, light_color.b);
	Renderer::BasicShader().SetUniform("u_light_pos", light_pos.r, light_pos.g, light_pos.b);

	Renderer::BasicShader().SetUniform("mat.ambient",   ambient.r,  ambient.g,  ambient.b);
	Renderer::BasicShader().SetUniform("mat.diffuse",   diffuse.r,  diffuse.g,  diffuse.b);
	Renderer::BasicShader().SetUniform("mat.specular", specular.r, specular.g, specular.b);
	Renderer::BasicShader().SetUniform("mat.shininess", shininess);
}

void graphics::MatBasic::Imgui(const char * name)
{
	ImGui::Begin(name);

	ImGui::ColorEdit3("Ambient", glm::value_ptr(ambient));

	ImGui::ColorEdit3("Diffuse", glm::value_ptr(diffuse));

	ImGui::ColorEdit3("Specular", glm::value_ptr(specular));

	ImGui::SliderFloat("Shininess", &shininess, 0.01f, 100.0f);

	ImGui::End();

}
