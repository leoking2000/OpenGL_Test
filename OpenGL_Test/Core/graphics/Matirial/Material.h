#pragma once
#include "leo_math.h"

namespace graphics
{
	class Matirial
	{
	public:
		virtual void Bind() const = 0;
		virtual void SetUniforms(const glm::mat4 model) = 0;

		virtual ~Matirial() {};
	};

}