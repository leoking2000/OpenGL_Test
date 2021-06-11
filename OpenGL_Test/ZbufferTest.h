#pragma once
#include "Scene.h"

#include "TextureEffect.h"
#include "InterColorEffect.h"

class ZbufferTest : public Scene
{
public:
	ZbufferTest()
		:
		tex("assets/w1.jpg"),
		cube1(graphics::MakeCube_TextureEffect(1)),
		cube2(graphics::MakeCube_InterColorEffect(1))
	{
	}

	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window) override
	{
		gfx_1.Init(in_canvas);
		gfx_2.Init(in_canvas);
		window = in_window;

		// cube 1
		cubetransform[0].Translate({ 0.0f, 0.0f, 2.0f });
		gfx_1.effect.vertex_shader.BindTransform(cubetransform[0]);
		gfx_1.effect.pixel_shader.BindTexture(tex);

		// cube 2
		cubetransform[1].Translate({ 0.0f, 0.0f, 4.0f });
		gfx_2.effect.vertex_shader.BindTransform(cubetransform[1]);
	}

	void Update(float dt) override
	{
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			if (t_press == false)
			{
				selected_cube_index = (selected_cube_index + 1) % 2;
				t_press = true;
			}
		}
		else
		{
			t_press = false;
		}

		float speed = 3.0f;

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].RotateX(speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].RotateX(-speed * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].RotateY(speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].RotateY(-speed * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].RotateZ(speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].RotateZ(-speed * dt);
		}

		// fordward 
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].Translate(glm::vec3(0.0f, 0.0f, speed) * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		{
			cubetransform[selected_cube_index].Translate(-glm::vec3(0.0f, 0.0f, speed) * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			glm::vec3& vec = gfx_1.effect.geometry_shader.light_dir;
			float z = cosf(speed * dt) * vec.z - sinf(speed * dt) * vec.x;
			float x = sinf(speed * dt) * vec.z + cosf(speed * dt) * vec.x;

			vec.x = x;
			vec.z = z;
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			glm::vec3& vec = gfx_1.effect.geometry_shader.light_dir;
			float z = cosf(-speed * dt) * vec.z - sinf(-speed * dt) * vec.x;
			float x = sinf(-speed * dt) * vec.z + cosf(-speed * dt) * vec.x;

			vec.x = x;
			vec.z = z;
		}


	}
	void Draw() override
	{
		gfx_1.DrawMesh(cube1);
		gfx_2.DrawMesh(cube2);
	}
private:
	graphics::Transform cubetransform[2];
	// for cube 1
	graphics::Texture tex;
	graphics::Mesh<graphics::TextureEffect::Vertex> cube1;
	graphics::Graphics<graphics::TextureEffect> gfx_1;
	// for cube 2
	graphics::Mesh<graphics::InterColorEffect::Vertex> cube2;
	graphics::Graphics<graphics::InterColorEffect> gfx_2;

	int selected_cube_index = 0;
	bool t_press = false;

	GLFWwindow* window;
};
