#pragma once
#include <GLFW/glfw3.h>
#include "Canvas.h"

class Game
{
public:
	~Game();

	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window);

	void Update(float dt);
	void Draw();

private:
	graphics::Canvas* canvas;
	GLFWwindow* window;
private:
	// Game Data
	float xPos = 450;
	float yPos = 450;
};

