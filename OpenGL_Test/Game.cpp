#include "Game.h"

Game::Game()
	:
	wood("assets/wood2.png"),
	wood_mc("assets/wood.png"),
	cube(graphics::MakeCube_TextureEffect(1))
{
}

void Game::Init(graphics::Canvas* in_canvas, GLFWwindow* in_window)
{
	gfx.Init(in_canvas);
	window = in_window;

	cubetransform.Translate(glm::vec3(0.0f, 0.0f, 3.0f));

	gfx.BindTransform(cubetransform);
	gfx.effect.pixel_shader.BindTexture(wood);
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	float speed = 3;

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		if (minecraft)
		{
			gfx.effect.pixel_shader.BindTexture(wood);
			minecraft = false;
		}
		else
		{
			gfx.effect.pixel_shader.BindTexture(wood_mc);
			minecraft = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		cubetransform.RotateX(speed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cubetransform.RotateX(-speed * dt);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cubetransform.RotateY(speed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cubetransform.RotateY(-speed * dt);
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		cubetransform.RotateZ(speed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		cubetransform.RotateZ(-speed * dt);
	}

	// fordward 
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		cubetransform.Translate(glm::vec3(0.0f, 0.0f, speed) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		cubetransform.Translate(-glm::vec3(0.0f, 0.0f, speed) * dt);
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		cubetransform.Translate(glm::vec3(speed, 0.0f, 0.0f) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		cubetransform.Translate(-glm::vec3(speed, 0.0f, 0.0f) * dt);
	}
}

void Game::Draw()
{
	gfx.DrawMesh(cube);
}
