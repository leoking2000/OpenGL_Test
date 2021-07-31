#include "MainWindow.h"
#include "OpenGL.h"
#include "Log.h"
#include "GLFW/glfw3.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"


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

bool Platform::CreateWindow(uint32_t width, uint32_t height, const char* win_name, bool resizable)
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.glfwwindow, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	return true;
}

bool Platform::isRunning()
{
	return !glfwWindowShouldClose(window.glfwwindow);
}

void Platform::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Platform::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window.glfwwindow);
	glfwPollEvents();
}

void Platform::Stop()
{
	glfwSetWindowShouldClose(window.glfwwindow, true);
}

void Platform::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window.glfwwindow);
	glfwTerminate();
}

uint32_t Platform::GetWidth()
{
	return window.width;
}

uint32_t Platform::GetHeight()
{
	return window.height;
}

void Platform::SetMouseVisibility(bool visible)
{
	glfwSetInputMode(window.glfwwindow, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

double Platform::GetMouseX()
{
	return window.mouseX;
}

double Platform::GetMouseY()
{
	return window.mouseY;
}

bool Platform::KeyIsPress(KEY key)
{
	switch (key)
	{
	case Platform::KEY_W:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_W) == GLFW_PRESS;
	case Platform::KEY_S:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_S) == GLFW_PRESS;
	case Platform::KEY_A:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_A) == GLFW_PRESS;
	case Platform::KEY_D:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_D) == GLFW_PRESS;
	case Platform::KEY_X:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_X) == GLFW_PRESS;
	case Platform::KEY_TAB:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_TAB) == GLFW_PRESS;
	case Platform::KEY_ESCAPE:
		return glfwGetKey(window.glfwwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	default:
		return false;
	}
}

void Platform::Resize(uint32_t width, uint32_t height)
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

void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	window.mouseX = xpos;
	window.mouseY = ypos;
}
