#pragma once
#include "Material.h"

namespace graphics
{
	class MatOneColor : public Matirial
	{
	public:
		glm::vec3 color;
	public:
		MatOneColor(const glm::vec3 color);

		void SetUniforms(const glm::mat4 model) override;
		void Imgui(const char* name) override;
	};

}