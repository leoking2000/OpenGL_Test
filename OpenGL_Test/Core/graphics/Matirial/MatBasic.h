#pragma once
#include "Material.h"
#include "Core/graphics/Abstractions/Texture.h"
#include "Core/graphics/Abstractions/Shader.h"

namespace graphics
{
	class MatBasic : public Matirial
	{
	public:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

		Shader shader;
		Texture tex;
	public:
		MatBasic(
			const glm::vec3& ambient,
			const glm::vec3& diffuse,
			const glm::vec3& specular,
			float shininess);

		MatBasic(const char* tex);

		void Bind() const override;
		void SetUniforms(const glm::mat4 model) override;
	};

}