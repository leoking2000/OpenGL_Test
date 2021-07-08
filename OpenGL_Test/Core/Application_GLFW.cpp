#include "GLFW/glfw3.h"

#include "Application.h"

#include "graphics/Renderer.h"

#include "utilities/Log.h"
#include <string>

using namespace graphics;

Core::Application::Application()
{
}

bool Core::Application::Init()
{
	if(!CreateWindow(900, 900, "OpenGL Test", true))
	{
		return false;
	}

	Logger::LogInfo("Application has initialized");

    return true;
}

int Core::Application::RunMainLoop()
{
	Logger::LogInfo("Main Loop has started");

	VartexArray va;

	// vertex buffer
	float vertexs[] = {
		// pos             // color             // tex cord
	   -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		0.5f,  0.5f,     0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
	   -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
	    0.5f, -0.5f,     0.0f, 1.0f, 0.0f,	  1.0f, 1.0f
	};

	VertexBuffer vb(vertexs, sizeof(vertexs));

	ElementType arr[3] = { FLOAT2, FLOAT3_N, FLOAT2 };
	Layout<3> layout(arr);
	va.AddBuffer(vb, layout);

	// index buffer
	uint32_t indices[] = { 0 , 1 , 2,
						   2 , 1 , 3 };
	IndexBuffer ib(indices, 6);

	float dt = ft.Mark();
	float dir = 1.0f;

	float Xoffset = 0.0f;
	float Yoffset = 0.0f;

	Texture tex("assets/earth.jpg");
	tex.Bind();

	Shader shader("Shader/Test.shader");

	Renderer renderer;

	GLFWwindow* window = (GLFWwindow*)GetHandle();

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		/////////////////////////////////////////////////////////
		
		shader.SetUniform("u_offset", Xoffset, Yoffset);
		shader.SetUniform("u_Tex", 0);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Yoffset += dt;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Yoffset -= dt;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Xoffset -= dt;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Xoffset += dt;
		}

		renderer.Draw(va, ib, shader);

	    ////////////////////////////////////////////////////////

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		{
			Logger::LogInfo(std::to_string(1.0f / ft.Mark()).c_str());
		}

		/////////////////////////////////////////////

		glfwSwapBuffers(window);
		glfwPollEvents();

		dt = ft.Mark();
	}

	return 0;
}

void Core::Application::TerminateApp()
{
	DestroyWindow();
}

