#pragma once
#include "Material.h"
#include "Core/graphics/Abstractions/Texture.h"
#include <memory>

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

		std::unique_ptr<Matirial> Copy()
		{
			return std::make_unique<MatBasic>(*this);
		}

		void Bind() const override;
		void SetUniforms(const glm::mat4 model) override;
	};

}