#pragma once
#include "Canvas.h"
#include "Mesh.h"
#include "Texture.h"


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

		void DrawTriangle(Vertex p0, Vertex p1, Vertex p2, const Texture& tex);
		void DrawMesh(const Mesh& in, const Transform& transform, const Texture& tex);

		
	private:
		static glm::ivec2 NDC_To_Canvas(const glm::vec3& vec);
		static void NDC_To_Canvas2(glm::vec3& vec);
		Canvas* canvas;
	};
}



