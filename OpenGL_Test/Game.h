#pragma once
#include <GLFW/glfw3.h>
#include "Graphics.h"

class Game
{
public:
	Game();
	~Game();

	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window);

	void Update(float dt);
	void Draw();

private:
	graphics::Graphics gfx;
	GLFWwindow* window;
private:
	// Game Data
	float xPos = 450;
	float yPos = 450;
	Mesh cube;
};

