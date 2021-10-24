#pragma once
#include "Core/graphics/Matirial/MatOneColor.h"
#include "Core/graphics/Mesh.h"
#include <memory>

namespace graphics
{
	class PointLight
	{
	public:
		glm::vec3 pos;
		glm::vec3 color;
	public:
		PointLight(const glm::vec3& pos, const glm::vec3& color);

		void Draw();
		void Imgui(const char* name);
	private:
		Mesh mesh;
	};
}