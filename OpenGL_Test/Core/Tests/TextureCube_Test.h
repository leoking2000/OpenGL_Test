#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"
#include "Math/math.h"

#include "Platform/MainWindow.h"
#include "GLFW/glfw3.h"

namespace Core
{
	class TextureCube_Test : public Test
	{
	public:
		TextureCube_Test(const char* filename)
			:
			tex(filename)
		{
			vertexArray.Bind();

			float vertexs[] = {
				// pos                 // tex cord      // normal
				// Forward
				-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f,  0.0f, -1.0f, //0
				-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f,  0.0f, -1.0f, //1
				 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f,  0.0f, -1.0f, //2
				 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f,  0.0f, -1.0f, //3
												  
				// EAST							  
				 0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    1.0f,  0.0f,  0.0f, //4
				 0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    1.0f,  0.0f,  0.0f, //5
				 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    1.0f,  0.0f,  0.0f, //6
				 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    1.0f,  0.0f,  0.0f, //7
												  
				// BACK							  
				 0.5f,  0.5f,  0.5f,     0.0f, 1.0f,    0.0f,  0.0f,  1.0f, //8
				 0.5f, -0.5f,  0.5f,     0.0f, 0.0f,    0.0f,  0.0f,  1.0f, //9
				-0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    0.0f,  0.0f,  1.0f, //10
				-0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    0.0f,  0.0f,  1.0f, //11
												  
				// WEST							  
				-0.5f, -0.5f, -0.5f,     1.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //12
				-0.5f,  0.5f, -0.5f,     1.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //13
				-0.5f,  0.5f,  0.5f,     0.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //14
				-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //15
												  
				// NORTH						  
				-0.5f,  0.5f, -0.5f,     0.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //16
				 0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //17
				 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //18
				-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //19
												  
				// SOUTH						  
				-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    0.0f, -1.0f,  0.0f,   //20
				 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   //21
				 0.5f, -0.5f,  0.5f,     1.0f, 1.0f,    0.0f, -1.0f,  0.0f,   //22
				-0.5f, -0.5f,  0.5f,     0.0f, 1.0f,    0.0f, -1.0f,  0.0f    //23
			};

			vertexBuffer.Recreate(vertexs, sizeof(vertexs));

			graphics::ElementType arr[3] = { graphics::FLOAT3, graphics::FLOAT2, graphics::FLOAT3_N };
			graphics::Layout<3> layout(arr);
			vertexArray.AddBuffer(vertexBuffer, layout);

			// index buffer
			uint32_t indices[] = { 
				// Forward
				0, 1, 2, /**/ 0, 2, 3,
				// EAST
				5, 4, 6, /**/ 5, 6, 7,
				// BACK
				9, 8, 10, /**/ 9, 10, 11,
				// WEST
				15, 14, 13, /**/ 15, 13, 12,
				// NORTH
				16, 19, 18, /**/ 16, 18, 17,
				// SOUTH
				22, 23, 20, /**/ 22, 20, 21
			};
			indexBuffer.Recreare(indices, 36);

			//shader
			const char* Shaderfilename = "Shaders/Basic3DShader.glsl";
			shader.Recreate(Shaderfilename);

			window = (GLFWwindow*)GetHandle();
			graphics::Renderer::SetClearColor(0.1f, 0.2f, 0.4f, 1.0f);

			rotation = glm::vec3(0.0f, 0.0f, 0.0f);
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

			if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
			{
				glm::mat4 a = glm::mat4(1.0f);
				a = glm::rotate(a, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
				light_dir = a * light_dir;
			}
			if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
			{
				glm::mat4 a = glm::mat4(1.0f);
				a = glm::rotate(a, -0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
				light_dir = a * light_dir;
			}

		}

		void Draw() override
		{
			glm::vec3 cubePositions[10] = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};


			view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, -0.0f, -10.0f));
			proj = glm::mat4(1.0f);
			proj = glm::perspective(glm::radians(45.0f), (float)GetWidth() / (float)GetHeight(), 0.1f, 100.0f);

			shader.Bind();
			tex.Bind();
			shader.SetUniform("view", view);
			shader.SetUniform("proj", proj);
			shader.SetUniform("u_light_dir", light_dir.x, light_dir.y, light_dir.z);

			for (int i = 0; i < 10; i++)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);

				model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

				shader.SetUniform("model", model);

				graphics::Renderer::Draw(vertexArray, indexBuffer, shader);
			}
	
		}

	private:
		graphics::VertexArray vertexArray;
		graphics::VertexBuffer vertexBuffer;
		graphics::IndexBuffer indexBuffer;
		graphics::Shader shader;

		graphics::Texture tex;

		glm::vec3 rotation;
		glm::vec4 light_dir{ 0.0f, 0.0f, -1.0f, 0.0f };

		glm::mat4 model; // object space -> world space
		glm::mat4 view;  // world space -> view/camera space
		glm::mat4 proj;  // projection

		GLFWwindow* window = nullptr;
	};
}