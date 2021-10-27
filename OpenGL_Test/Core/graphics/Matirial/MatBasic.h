#pragma once
#include "Material.h"

namespace graphics
{
	class MatBasic : public Matirial
	{
	public:
		glm::vec3 color;
		float ambient;
		float diffuse;
		float specular;
		float shininess;

	public:
		MatBasic(float red, float green, float blue);
		MatBasic(const glm::vec3& color);
		MatBasic(const glm::vec3& color,
			float ambient,
			float diffuse,
			float specular,
			float shininess);

		void SetUniforms(const glm::mat4 model) override;
		void Imgui(const char* name) override;
	};

}