#pragma once
#include <GLFW/glfw3.h>
#include "FrameTimer.h"

#define WIDTH 900
#define HEIGHT 900

class Application
{
public:
	Application();
	bool Init();
	int RunMainLoop();
	void TerminateApp();

private:
	GLFWwindow* m_window = nullptr;
	FrameTimer ft;
private:

};

