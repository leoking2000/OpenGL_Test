#pragma once
#include "GLFW/glfw3.h"
#include "Test.h"
#include "Core/graphics/Renderer.h"
#include "Platform/MainWindow.h"
#include "Math/math.h"

namespace Core
{
	class Triangles2D_Test : public Test
	{
	public:
		Triangles2D_Test()
			: tex(1, 1, Colors::White)
		{
			// vertex buffer
			float vertexs[] = {
				// pos             // color             // tex cord
				0.0f,  0.5f, -1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // 0
				0.5f, -0.5f, -1.0f,    0.0f, 1.0f, 0.0f,	1.0f, 1.0f, // 1
			   -0.5f, -0.5f, -1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f, // 2

			    0.0f,  -0.5f, -1.0f,    1.0f, 0.0f, 1.0f,   1.0f, 0.0f, // 3
				0.25f, 00.0f, -1.0f,    1.0f, 1.0f, 0.0f,	1.0f, 1.0f, // 4
			   -0.25f, 00.0f, -1.0f,    0.0f, 1.0f, 1.0f,	1.0f, 1.0f  // 5
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
			float speed = 1.0f;

			GLFWwindow* window = (GLFWwindow*)GetHandle();

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				pos.y = Math::wrap_angle(pos.y + speed * dt);
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				pos.y = Math::wrap_angle(pos.y - speed * dt);
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				pos.x = Math::wrap_angle(pos.x - speed * dt);
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				pos.x = Math::wrap_angle(pos.x + speed * dt);
			}

			shader.SetUniform("u_offset", pos.x, pos.y);
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

		glm::vec3 pos;
	};
}