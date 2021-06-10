#pragma once
#include "Scene.h"
#include "SolidGeometryEffect.h"
#include "Colors.h"

class SolidCubeScene : public Scene
{
public:
	SolidCubeScene()
		:
		cube(graphics::MakeCube_SolidGeometryEffect(1.0f))
	{
	}
	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window) override
	{
		gfx.Init(in_canvas);
		window = in_window;

		cubetransform.Translate({ 0.0f, 0.0f, 2.0f });
		gfx.effect.vertex_shader.BindTransform(cubetransform);
		gfx.effect.geometry_shader.BindColors({ Colors::Blue, Colors::Cyan, Colors::Gray, Colors::Green, Colors::Red, Colors::LightGray });
	}

	void Update(float dt) override
	{
		float speed = 3.0f;

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
	}
	void Draw() override
	{
		gfx.DrawMesh(cube);
	}

private:
	graphics::Graphics<graphics::SolidGeometryEffect> gfx;
	graphics::Mesh<graphics::SolidGeometryEffect::Vertex> cube;
	graphics::Transform cubetransform;
	GLFWwindow* window;
};