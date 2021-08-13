#include "MatBasic.h"
#include "Core/graphics/Abstractions/Shader.h"
#include "Core/graphics/Renderer.h"

static graphics::Shader shader;
static bool shaderIsInsialized = false;

graphics::MatBasic::MatBasic(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
	:
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess),
	tex(1,1,Colors::White)
{
	if (shaderIsInsialized == false)
	{
		shader.Recreate("Shaders/Basic.glsl");
		shaderIsInsialized = true;
	}
}

graphics::MatBasic::MatBasic(const char* tex)
	:
	ambient(0.1f, 0.1f, 0.1f),
	diffuse(1.0f, 1.0f, 1.0f),
	specular(0.5f, 0.5f, 0.5f),
	shininess(64.0f),
	tex(tex)
{
	if (shaderIsInsialized == false)
	{
		shader.Recreate("Shaders/Basic.glsl");
		shaderIsInsialized = true;
	}
}

void graphics::MatBasic::Bind() const
{
	shader.Bind();
	tex.Bind(0);
}

void graphics::MatBasic::SetUniforms(const glm::mat4 model)
{
	shader.SetUniform("proj", graphics::Renderer::proj);
	shader.SetUniform("view", graphics::Renderer::cam.GetCameraView());
	shader.SetUniform("model", model);

	shader.SetUniform("u_Tex", 0);

	shader.SetUniform("u_light_color", 1.0f, 1.0f, 1.0f);
	shader.SetUniform("u_light_pos", 0.0f, 0.0f, 0.0f);

	shader.SetUniform("mat.ambient",   ambient.r,  ambient.g,  ambient.b);
	shader.SetUniform("mat.diffuse",   diffuse.r,  diffuse.g,  diffuse.b);
	shader.SetUniform("mat.specular", specular.r, specular.g, specular.b);
	shader.SetUniform("mat.shininess", shininess);
}
