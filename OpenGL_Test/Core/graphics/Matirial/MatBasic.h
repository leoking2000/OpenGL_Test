#pragma once
#include "Material.h"
#include "Core/graphics/Abstractions/Texture.h"

namespace graphics
{
	class MatBasic : public Matirial
	{
	public:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

		Texture tex;
	public:
		MatBasic(
			const glm::vec3& ambient,
			const glm::vec3& diffuse,
			const glm::vec3& specular,
			float shininess);

		MatBasic(const char* tex);

		void SetUniforms(const glm::mat4 model) override;
		void Imgui(const char* name) override;
	};

}