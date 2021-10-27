#pragma once
#include "Material.h"
#include "Core/graphics/Abstractions/Texture.h"

namespace graphics
{
	class MatBasicTex : public Matirial
	{
	public:
		Texture tex;
		float ambient;
		float diffuse;
		float specular;
		float shininess;

	public:
		MatBasicTex(const char* name);
		MatBasicTex(const char* name,
			float ambient,
			float diffuse,
			float specular,
			float shininess);

		void SetUniforms(const glm::mat4 model) override;
		void Imgui(const char* name) override;
	};

}