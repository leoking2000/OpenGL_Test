#include "MatBasicTex.h"
#include "Core/graphics/Renderer.h"
#include "../imgui/imgui.h"

graphics::MatBasicTex::MatBasicTex(const char* name)
	:
	tex(name),
	ambient(0.1f),
	diffuse(0.9f),
	specular(0.9f),
	shininess(200.0f)
{
}

graphics::MatBasicTex::MatBasicTex(const char* name, float ambient, float diffuse, float specular, float shininess)
	:
	tex(name),
	ambient(0.1f),
	diffuse(0.9f),
	specular(0.9f),
	shininess(200.0f)
{
}

void graphics::MatBasicTex::SetUniforms(const glm::mat4 model)
{
	Renderer::BasicTexShader().Bind();

	Renderer::BasicTexShader().SetUniform("proj", graphics::Renderer::Proj());
	Renderer::BasicTexShader().SetUniform("view", graphics::Renderer::MainCamera().GetCameraView());
	Renderer::BasicTexShader().SetUniform("model", model);

	glm::vec3 light_pos = Renderer::MainLight().pos;
	glm::vec3 light_color = Renderer::MainLight().color;

	Renderer::BasicTexShader().SetUniform("u_light_color", light_color.r, light_color.g, light_color.b);
	Renderer::BasicTexShader().SetUniform("u_light_pos", light_pos.r, light_pos.g, light_pos.b);

	tex.Bind(0);
	Renderer::BasicTexShader().SetUniform("texture_diffuse", 0);

	Renderer::BasicTexShader().SetUniform("mat.ambient",   ambient,  ambient,  ambient);
	Renderer::BasicTexShader().SetUniform("mat.diffuse",   diffuse,  diffuse,  diffuse);
	Renderer::BasicTexShader().SetUniform("mat.specular", specular, specular, specular);
	Renderer::BasicTexShader().SetUniform("mat.shininess", shininess);
}

void graphics::MatBasicTex::Imgui(const char* name)
{
}
