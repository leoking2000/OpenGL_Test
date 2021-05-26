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
	Texture wood;
	Texture book;
	Texture earth;
	Mesh<TexVertex> cube;
	Transform cubetransform = {};
};

