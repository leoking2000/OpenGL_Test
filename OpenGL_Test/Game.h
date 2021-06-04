#pragma once
#include "Scene.h"
#include <memory>

class Game
{
public:
	Game();
	~Game();

	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window);

	void Update(float dt);
	void Draw();

private:
	// Game Data
	std::vector<std::unique_ptr<Scene>> scenes;
	int current_scene_index = 0;

	bool tab_press = false;
	GLFWwindow* window;
};

