#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

namespace Core
{
	class Triangle2D : public Test
	{
	public:
		Triangle2D()
			: tex(1, 1, Colors::White)
		{
			// vertex buffer
			float vertexs[] = {
				// pos             // color             // tex cord
				0.0f,  0.5f, -1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, // 0
				0.5f, -0.5f, -1.0f,    1.0f, 1.0f, 1.0f,	1.0f, 1.0f, // 1
			   -0.5f, -0.5f, -1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // 2

			    0.0f,  -0.5f, -1.0f,    1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // 3
				0.25f, 00.0f, -1.0f,    1.0f, 1.0f, 1.0f,	1.0f, 1.0f, // 4
			   -0.25f, 00.0f, -1.0f,    1.0f, 1.0f, 1.0f,	1.0f, 1.0f  // 5
			};

			vertexBuffer.Recreate(vertexs, sizeof(vertexs));

			graphics::ElementType arr[3] = { graphics::FLOAT3, graphics::FLOAT3_N, graphics::FLOAT2 };
			graphics::Layout<3> layout(arr);
			vertexArray.AddBuffer(vertexBuffer, layout);

			// index buffer
			uint32_t indices[] = { 0 , 4 , 5,
								   1 , 3 , 4,
								   2 , 3 , 5 };
			indexBuffer.Recreare(indices, 9);

			//shader
			shader.Recreate("Shaders/Test.shader");

			graphics::Renderer::SetClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		}

		void Update(float dt) override
		{

		}

		void Draw() override
		{
			tex.Bind();
			graphics::Renderer::Draw(vertexArray, indexBuffer, shader);
		}


	private:
		graphics::VertexArray vertexArray;
		graphics::VertexBuffer vertexBuffer;
		graphics::IndexBuffer indexBuffer;
		graphics::Shader shader;
		graphics::Texture tex;
	};
}