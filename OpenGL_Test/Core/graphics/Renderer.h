#pragma once
#include <cinttypes>
#include "Abstractions/VertexArray.h"
#include "Abstractions/IndexBuffer.h"
#include "Abstractions/Shader.h"
#include "Abstractions/Texture.h"

#include "Math/math.h"

namespace graphics
{
	class Renderer
	{
	public:
		static void Init();

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();

		static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

	public:
		static glm::mat4 proj;

	};
}



