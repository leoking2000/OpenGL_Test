#include <GL/glew.h>

#include "Application.h"

#include "utilities.h"
#include "Log.h"
#include <string>

Application::Application()
{
}

bool Application::Init()
{
	// Set GLFW error callback
	glfwSetErrorCallback(Logger::LogGLFW_Error);

	// Initialize GLFW
	if (!glfwInit())
	{
		Logger::LogError("GLFW could not Initialize.");
		return false;
	}

	// Hits
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Creating a Window.
	m_window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL test", NULL, NULL);
	if (!m_window)
	{
		Logger::LogError("Window creation failed.");
		glfwTerminate();
		return false;
	}

	//Making the OpenGL context current
	glfwMakeContextCurrent(m_window);
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("GLEW could not Initialize.");
		return false;
	}

	// print OpenGL version
	Logger::LogInfo((const char*)glGetString(GL_VERSION));

	glfwSwapInterval(1);

	// Tell OpenGL how big is the window
	glCall(glViewport(0, 0, WIDTH, HEIGHT));

    return true;
}

int Application::RunMainLoop()
{
	float dt = ft.Mark();

	// Main Loop
	while (!glfwWindowShouldClose(m_window))
	{

		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_window, true);
		}

		if (glfwGetKey(m_window, GLFW_KEY_K) == GLFW_PRESS)
		{
			Logger::LogInfo(std::to_string(1.0f / ft.Mark()).c_str());
		}

		glfwSwapBuffers(m_window);
		glfwPollEvents();

		dt = ft.Mark();
	}

	return 0;
}

void Application::TerminateApp()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

