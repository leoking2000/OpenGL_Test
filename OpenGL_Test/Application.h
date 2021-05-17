#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "utilities.h"
#include "Log.h"
#include "FrameTimer.h"

#define DEFAULT_WIDTH 900
#define DEFAULT_HEIGHT 900

class Application
{
public:
	Application();
	bool Init();
	int RunMainLoop();
	void TerminateApp();

private:
	GLFWwindow* m_window = nullptr;
	const uint32_t m_width  = DEFAULT_WIDTH;
	const uint32_t m_height = DEFAULT_HEIGHT;
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

