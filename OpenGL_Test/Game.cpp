#include "Game.h"

void Game::Init(graphics::Canvas* in_canvas, GLFWwindow* in_window)
{
	gfx.Init(in_canvas);
	window = in_window;

	cube.Translate(glm::vec3(0.0f, 0.0f, 1.5f));
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
	float speed = 2;

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

	// fordward 
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		cube.Translate(glm::vec3(0.0f, 0.0f, speed) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		cube.Translate(-glm::vec3(0.0f, 0.0f, speed) * dt);
	}

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		cube.Translate(glm::vec3(speed, 0.0f, 0.0f) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		cube.Translate(-glm::vec3(speed, 0.0f, 0.0f) * dt);
	}
}

void Game::Draw()
{
	gfx.DrawMesh(cube.GetTransformMesh());
}
