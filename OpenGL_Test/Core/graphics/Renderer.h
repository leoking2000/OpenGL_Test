#pragma once
#include <cinttypes>
#include "VartexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace graphics
{
	class Renderer
	{
	public:
		void Draw(const VartexArray& va, const IndexBuffer& ib, const Shader& shader);

	};
}



