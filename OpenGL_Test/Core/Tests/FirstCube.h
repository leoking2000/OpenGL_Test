#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"
#include "Math/math.h"

#include "Platform/MainWindow.h"
#include "GLFW/glfw3.h"

namespace Core
{
	class FirstCube : public Test
	{
	public:
		FirstCube()
		{
			// vertex buffer
			float vertexs[] = {
				// pos                 // color      
			   -0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,  //0
			   -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f,  //1
			    0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 1.0f,  //2
				0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,  //3
			    0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,  //4
				0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f,  //5
			   -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,  //6
			   -0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 0.0f   //7
			};

			vertexBuffer.Recreate(vertexs, sizeof(vertexs));

			graphics::ElementType arr[2] = { graphics::FLOAT3, graphics::FLOAT3_N };
			graphics::Layout<2> layout(arr);
			vertexArray.AddBuffer(vertexBuffer, layout);

			// index buffer
			uint32_t indices[] = { 1 , 6 , 4,   /**/  1 , 4 , 2,
								   5 , 7 , 0,   /**/  5 , 0 , 3, 
								   7 , 6 , 1,   /**/  7 , 1 , 0,
								   3 , 2 , 4,   /**/  3 , 4 , 5,
								   5 , 4 , 6,   /**/  5 , 6 , 7,
								   0 , 1 , 2,   /**/  0 , 2 , 3
			};
			indexBuffer.Recreare(indices, 36);

			//shader
			const char* filename = "Shaders/first_cube.shader";
			shader.Recreate(filename);

			window = (GLFWwindow*)GetHandle();
		}

		void Update(float dt) override
		{
			float speed = 1.0f;

			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			{
				rotation.x = Math::wrap_angle(rotation.x + speed * dt);
			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				rotation.x = Math::wrap_angle(rotation.x - speed * dt);
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				rotation.y = Math::wrap_angle(rotation.y + speed * dt);
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				rotation.y = Math::wrap_angle(rotation.y - speed * dt);
			}

			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			{
				rotation.z = Math::wrap_angle(rotation.z + speed * dt);
			}
			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			{
				rotation.z = Math::wrap_angle(rotation.z - speed * dt);
			}

			shader.SetUniform("u_rotation", rotation.x, rotation.y, rotation.z);
		}

		void Draw() override
		{
			graphics::Renderer::Draw(vertexArray, indexBuffer, shader);
		}

	private:
		graphics::VertexArray vertexArray;
		graphics::VertexBuffer vertexBuffer;
		graphics::IndexBuffer indexBuffer;
		graphics::Shader shader;

		Math::Vector3 rotation;

		GLFWwindow* window = nullptr;
	};
}