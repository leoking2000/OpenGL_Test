#pragma once
#include "leo_math.h"

namespace graphics
{
	class Matirial
	{
	public:
		virtual void SetUniforms(const glm::mat4 model) = 0;
		virtual void Imgui(const char* name) = 0;

		virtual ~Matirial() {};
	};

}