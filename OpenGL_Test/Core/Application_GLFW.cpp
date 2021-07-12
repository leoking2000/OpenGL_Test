#include "GLFW/glfw3.h"

#include "Application.h"

#include "graphics/Renderer.h"

#include "Tests/RenderTexture.h"
#include "Tests/Triangles2D_Test.h"
#include "Tests/FirstCube.h"

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
	Renderer::Init();
	/////////////////////////////////////////////////////////

	tests.push_back(new FirstCube());
	//tests.push_back(new Triangles2D_Test());
	//tests.push_back(new RenderTexture("assets/earth.jpg"));
	//tests.push_back(new RenderTexture("assets/sun.jpg"));


	/////////////////////////////////////////////////////////
	Logger::LogInfo("Application has initialized");
    return true;
}

int Core::Application::RunMainLoop()
{
	Logger::LogInfo("Main Loop has started");

	float dt = ft.Mark();
	GLFWwindow* window = (GLFWwindow*)GetHandle();

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		/////////////////////////////////////////////////////////
		Renderer::Clear();

		tests[current_test_index]->Update(dt);
		tests[current_test_index]->Draw();

	    ////////////////////////////////////////////////////////

		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		{
			if (tab_press == false)
			{
				current_test_index = (current_test_index + 1) % tests.size();
				tab_press = true;
			}
		}
		else
		{
			tab_press = false;
		}

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
	for (Test* p : tests)
	{
		delete p;
	}

	DestroyWindow();
}

