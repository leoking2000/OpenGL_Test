#include "Game.h"

void Game::Init(graphics::Canvas* in_canvas, GLFWwindow* in_window)
{
	gfx.Init(in_canvas);
	window = in_window;
}

Game::Game()
	:
	cube(Mesh::MakeCube(1))
{
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	float speed = 1;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		cube.RotateX(speed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cube.RotateX(-speed * dt);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cube.RotateY(speed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cube.RotateY(-speed * dt);
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		cube.RotateZ(speed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		cube.RotateZ(-speed * dt);
	}
}

void Game::Draw()
{
	gfx.DrawMesh(cube.GetTransformMesh());
}
