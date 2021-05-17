#include "Game.h"

void Game::Init(graphics::Canvas* in_canvas, GLFWwindow* in_window)
{
	canvas = in_canvas;
	window = in_window;
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	float speed = 100;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		yPos -= speed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		yPos += speed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		xPos += speed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		xPos -= speed * dt;
	}
}

void Game::Draw()
{
	for (int y = (int)yPos - 100; y < (int)yPos + 100; y++)
	{
		for (int x = (int)xPos - 100; x < (int)xPos + 100; x++)
		{
			if (y >= 0 && y < WIDTH && x >= 0 && x < HEIGHT)
			{
				canvas->PutPixel(x, y, { 0, 100, 10 });
			}
		}
	}

	if (yPos >= 0 && yPos < WIDTH && xPos >= 0 && xPos < HEIGHT)
	{
		canvas->DrawLine((uint32_t)xPos, (uint32_t)yPos, 450, 450, { 255, 0, 0 });
	}
}
