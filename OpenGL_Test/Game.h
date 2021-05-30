#pragma once
#include <GLFW/glfw3.h>
#include "Graphics.h"

#include "TextureEffect.h"

class Game
{
public:
	Game();
	~Game();

	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window);

	void Update(float dt);
	void Draw();

private:
	graphics::Graphics<graphics::TextureEffect> gfx;
	GLFWwindow* window;
private:
	// Game Data
	bool minecraft = false;
	graphics::Texture wood_mc;
	graphics::Texture wood;
	graphics::Mesh<graphics::TextureEffect::Vertex> cube;
	graphics::Transform cubetransform = {};
};

