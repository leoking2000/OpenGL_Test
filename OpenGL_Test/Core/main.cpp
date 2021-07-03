#include <GL/glew.h>
#include "Application.h"

#include "utilities.h"
#include "Log.h"

GLFWwindow* Init()
{
	// Set GLFW error callback
	glfwSetErrorCallback(Logger::LogGLFW_Error);

	// Initialize GLFW
	if (!glfwInit())
	{
		Logger::LogError("GLFW could not Initialize.");
		return nullptr;
	}

	// Hits
	// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// using the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// maiking the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Creating a Window.
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL test", NULL, NULL);
	if (!window)
	{
		Logger::LogError("Window creation failed.");
		return nullptr;
	}

	//Making the OpenGL context current
	glfwMakeContextCurrent(window);
	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("GLEW could not Initialize.");
		return nullptr;
	}

	// print OpenGL version
	Logger::LogInfo((const char*)glGetString(GL_VERSION));

	glfwSwapInterval(1);

	// Tell OpenGL how big is the window
	glCall(glViewport(0, 0, WIDTH, HEIGHT));

	return window;
}

int main() 
{
	GLFWwindow* window = Init();
	int return_code = -1;

	if (window)
	{
		Application app(window);

		if (app.Init())
		{
			return_code = app.RunMainLoop();
		}

		app.TerminateApp();
	}
	else
	{
		return return_code;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return return_code;
}

