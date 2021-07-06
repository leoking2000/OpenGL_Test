#include "MainWindow.h"
#include "OpenGL.h"
#include "GLFW/glfw3.h"
#include "Core/utilities/Log.h"


struct MainWindow
{
	GLFWwindow* glfwwindow;
	uint32_t width;
	uint32_t height;
};

static MainWindow window;

void window_size_callback(GLFWwindow* window, int width, int height);

bool Core::CreateWindow(uint32_t width, uint32_t height, const char* win_name, bool resizable)
{
	static bool init = false;
	assert(!init);

	// Set GLFW error callback
	glfwSetErrorCallback(Logger::LogGLFW_Error);

	// Initialize GLFW
	if (!glfwInit())
	{
		Logger::LogError("GLFW could not Initialize.");
		return false;
	}

	// Hits
	// OpenGL version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// using the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// maiking the window not resizable
	glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);

	// Creating a Window.
	window.glfwwindow = glfwCreateWindow(width, height, win_name, NULL, NULL);
	if (!window.glfwwindow)
	{
		Logger::LogError("Window creation failed.");
		return false;
	}

	glfwSetWindowSizeCallback(window.glfwwindow, window_size_callback);

	//Making the OpenGL context current
	glfwMakeContextCurrent(window.glfwwindow);

	// Initialize OpenGL
	if (!InitOpenGL())
	{
		Logger::LogError("OpenGL could not Initialize.");
		return false;
	}

	// print OpenGL version
	Logger::LogInfo((const char*)glGetString(GL_VERSION));

	glfwSwapInterval(1);

	// Tell OpenGL how big is the window
	glCall(glViewport(0, 0, width, height));

	window.width = width;
	window.height = height;

	init = true;

	return true;
}

void Core::DestroyWindow()
{
	glfwDestroyWindow(window.glfwwindow);
	glfwTerminate();
}

inline uint32_t Core::GetWidth()
{
	return window.width;
}

inline uint32_t Core::GetHeight()
{
	return window.height;
}

void* Core::GetHandle()
{
	return window.glfwwindow;
}

void Core::Resize(uint32_t width, uint32_t height)
{
	glfwSetWindowSize(window.glfwwindow, (int)width, (int)height);
	
	window_size_callback(window.glfwwindow, (int)width, (int)height);
}

void window_size_callback(GLFWwindow* _window, int width, int height)
{
	glCall(glViewport(0, 0, width, height));

	window.width = width;
	window.height = height;
}
