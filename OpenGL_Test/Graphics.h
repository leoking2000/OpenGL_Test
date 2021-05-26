#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Canvas.h"
#include "Mesh.h"


namespace graphics
{
	/*
	* Draws to canvas using as input NDC
	* it also does z-divide (perspective-divide)
	* x: -1.0 -> 1.0
	* y: -1.0 -> 1.0
	* z:  0.0 -> 1.0 (not including 0)
	*/
	class Graphics
	{
	public:
		void Init(Canvas* a);

		void DrawLine(const glm::vec3& a, const glm::vec3& b, const Color& c);
		void DrawWireframeTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const Color& color);
		void DrawTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, const Color& c);
		void DrawTriangle(TexVertex p0, TexVertex p1, TexVertex p2);

		void DrawMesh(Mesh<Vertex> a);

		void DrawMeshTex(Mesh<TexVertex> a);

		static glm::ivec2 NDC_To_Canvas(const glm::vec3& vec);
	private:
		Canvas* canvas;
	};
}



