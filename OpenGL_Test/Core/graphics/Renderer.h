#pragma once
#include <cinttypes>
#include "Mesh.h"
#include "Abstractions/Shader.h"
#include "Abstractions/Texture.h"
#include "Matirial/Material.h"
#include "Light/PointLight.h"
#include "Camera.h"

namespace graphics
{
	class Renderer
	{
	public:
		static void CleanUp();

		static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
		static void Draw(const Matirial* mat, const Mesh& mesh);

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();

		static Camera& MainCamera();
		static glm::mat4 Proj();

		static Shader& BasicShader();
		static Shader& BasicTexShader();
		static Shader& OneColorShader();

		static PointLight& MainLight();

	public:
		Renderer(const Renderer&) = delete;
		void operator=(const Renderer&) = delete;
	private:
		glm::mat4 proj;
		Camera cam;

		Shader basicShader;
		Shader basicTexShader;
		Shader oneColorShader;

		PointLight light;
	private:
		Renderer();
		static Renderer& Get();
	private:
		static Renderer* instance;
	};
}



