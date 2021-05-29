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

		void BindTransform(const Transform& in_transform);
		void BindTexture(const Texture& in_tex);

		void DrawLine(const glm::vec3& a, const glm::vec3& b, const Color& c);
		void DrawWireframeTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const Color& color);

		void DrawMesh(const Mesh& in, const Transform& transform, const Texture& tex);
		void DrawMesh(const Mesh& in);
	private:
		// pipeline
		void ProcessVertices(const Mesh& mesh);    // model -> world (copy)
		void AssembleTriangles(Mesh& mesh);  // assemble triagles using index list and does Backface Culling
		void ProcessTriangle(Vertex& v0, Vertex& v1, Vertex& v2); // geometry shader???
		void PostProcessTriangleVertices(Vertex v0, Vertex v1, Vertex v2); // world -> view (perspective)
		void DrawTriangle(Vertex& v0, Vertex& v1, Vertex& v2); // wat this do?
	private:
		void DrawFlatTopTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2);
		void DrawFlatBottomTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2);
		void DrawFlatTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2,
			                  const Vertex& dv0, const Vertex& dv1, Vertex itEdge1);
	private:
		static glm::ivec2 NDC_To_Canvas(const glm::vec3& vec);
		static void NDC_To_Canvas2(glm::vec3& vec);
	private:
		Canvas* canvas;

		const Transform* transform = nullptr;
		const Texture* texture = nullptr;
	};
}



