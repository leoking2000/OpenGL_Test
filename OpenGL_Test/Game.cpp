#include "Game.h"

#include "LoadObjScene.h"

Game::Game()
{
}

void Game::Init(graphics::Canvas* in_canvas, GLFWwindow* in_window)
{
	window = in_window;
	
	scenes.push_back(std::make_unique<LoadObjScene>("assets/tea.obj", 0.1f));
	scenes.push_back(std::make_unique<LoadObjScene>("assets/ccw_m.obj", 1.0f));
	scenes.push_back(std::make_unique<LoadObjScene>("assets/ccw_object1.obj", 1.0f));
	scenes.push_back(std::make_unique<LoadObjScene>("assets/plane.obj", 1.0f));

	for (auto& scene : scenes)
	{
		scene->Init(in_canvas, in_window);
	}
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (tab_press == false)
		{
			current_scene_index = (current_scene_index + 1) % scenes.size();
			tab_press = true;
		}
	}
	else
	{
		tab_press = false;
	}

	scenes[current_scene_index]->Update(dt);

}

void Game::Draw()
{
	scenes[current_scene_index]->Draw();
}
