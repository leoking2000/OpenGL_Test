#pragma once
#include <GLFW/glfw3.h>
#include "FrameTimer.h"

#define WIDTH 900
#define HEIGHT 900

class Application
{
public:
	Application(GLFWwindow* window);
	bool Init();
	int RunMainLoop();
	void TerminateApp();

private:
	GLFWwindow* m_window;
	FrameTimer ft;
private:
	uint32_t VertexArray;
	uint32_t ShaderProgram;

};

