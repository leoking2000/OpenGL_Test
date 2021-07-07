#pragma once
#include <cinttypes>
#include "Abstractions/VartexArray.h"
#include "Abstractions/IndexBuffer.h"
#include "Abstractions/Shader.h"

namespace graphics
{
	class Renderer
	{
	public:
		void SetClearColor(float r, float g, float b, float a);
		void Draw(const VartexArray& va, const IndexBuffer& ib, const Shader& shader);

	};
}



