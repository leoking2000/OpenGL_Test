#pragma once
#include <GLFW/glfw3.h>
#include "Graphics.h"

class Scene
{
public:
	virtual void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window) = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
};
