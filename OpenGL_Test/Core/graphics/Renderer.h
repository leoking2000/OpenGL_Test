#pragma once
#include <cinttypes>
#include "Mesh.h"
#include "Abstractions/Shader.h"
#include "Abstractions/Texture.h"
#include "Matirial/Material.h"
#include "Camera.h"

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

		static void Draw(const Matirial* mat, const Mesh& mesh);

	public:
		static glm::mat4 proj;
		static Camera cam;
	};
}



