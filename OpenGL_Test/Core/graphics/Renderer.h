#pragma once
#include <cinttypes>
#include "Abstractions/VertexArray.h"
#include "Abstractions/IndexBuffer.h"
#include "Abstractions/Shader.h"
#include "Abstractions/Texture.h"
#include "Camera.h"
#include "GameObject.h"

#include "leo_math.h"

namespace graphics
{
	class Renderer
	{
	public:
		static void Init();

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();

		static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

		static void Draw(const GameObject& obj);

	public:
		static glm::mat4 proj;
		static Camera cam;
		static GameObject light;
	};
}



