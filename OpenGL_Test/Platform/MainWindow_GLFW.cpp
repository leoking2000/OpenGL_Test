#include "MainWindow.h"
#include "OpenGL.h"
#include "GLFW/glfw3.h"
#include "Core/utilities/Log.h"


struct MainWindow
{
	GLFWwindow* glfwwindow;
	uint32_t width;
	uint32_t height;

	double mouseX;
	double mouseY;
};

static MainWindow window;

void window_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

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

	glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);

	window.glfwwindow = glfwCreateWindow(width, height, win_name, NULL, NULL);
	if (!window.glfwwindow)
	{
		Logger::LogError("Window creation failed.");
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(window.glfwwindow, window_size_callback);

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

	glCall(glViewport(0, 0, width, height));

	window.width = width;
	window.height = height;

	glfwSetCursorPosCallback(window.glfwwindow, mouse_callback);

	init = true;

	return true;
}

void Core::DestroyWindow()
{
	glfwDestroyWindow(window.glfwwindow);
	glfwTerminate();
}

uint32_t Core::GetWidth()
{
	return window.width;
}

uint32_t Core::GetHeight()
{
	return window.height;
}

void Core::SetMouseVisibility(bool visible)
{
	glfwSetInputMode(window.glfwwindow, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

double Core::GetMouseX()
{
	return window.mouseX;
}

double Core::GetMouseY()
{
	return window.mouseY;
}

bool Core::KeyIsPress(KEY key)
{
	switch (key)
	{
	case Core::KEY_W:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_W) == GLFW_PRESS;
	case Core::KEY_S:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_S) == GLFW_PRESS;
	case Core::KEY_A:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_A) == GLFW_PRESS;
	case Core::KEY_D:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_D) == GLFW_PRESS;
	case Core::KEY_X:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_X) == GLFW_PRESS;
	case Core::KEY_TAB:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_TAB) == GLFW_PRESS;
	case Core::KEY_ESCAPE:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	default:
		return false;
	}
}

void Core::Resize(uint32_t width, uint32_t height)
{
	glfwSetWindowSize(window.glfwwindow, (int)width, (int)height);
	
	window_size_callback(window.glfwwindow, (int)width, (int)height);
}

void* Core::GetHandle()
{
	return window.glfwwindow;
}

void window_size_callback(GLFWwindow* _window, int width, int height)
{
	glCall(glViewport(0, 0, width, height));

	window.width = width;
	window.height = height;
}

void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	window.mouseX = xpos;
	window.mouseY = ypos;
}
