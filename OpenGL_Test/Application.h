#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "utilities.h"
#include "Log.h"
#include "FrameTimer.h"

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

	Game game;

	// canvas 
	graphics::Canvas m_canvas;
	uint32_t m_CanvasShader;
	uint32_t m_CanvasTexture;
	uint32_t m_VAO_Canvas;
	uint32_t m_IndixBuffer_Canavas;
private:
	void InitCanvas();
	void RenderCanvas();

};

