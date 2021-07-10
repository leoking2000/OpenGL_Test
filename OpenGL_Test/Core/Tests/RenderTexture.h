#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

namespace Core
{
	class RenderTexture : public Test
	{
	public:
		RenderTexture(const char* filename)
			: tex(filename)
		{
			// vertex buffer
			float vertexs[] = {
				// pos             // color             // tex cord
			   -1.0f,  1.0f,     1.0f, 1.0f, 1.0f,    0.0f, 0.0f,
				1.0f,  1.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
			   -1.0f, -1.0f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
				1.0f, -1.0f,     1.0f, 1.0f, 1.0f,	  1.0f, 1.0f
			};

			vertexBuffer.Recreate(vertexs, sizeof(vertexs));

			graphics::ElementType arr[3] = { graphics::FLOAT2, graphics::FLOAT3_N, graphics::FLOAT2 };
			graphics::Layout<3> layout(arr);
			vertexArray.AddBuffer(vertexBuffer, layout);

			// index buffer
			uint32_t indices[] = { 0 , 1 , 2,
								   2 , 1 , 3 };
			indexBuffer.Recreare(indices, 6);

			//shader
			shader.Recreate("Shader/Test.shader");
		}

		~RenderTexture() override
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
