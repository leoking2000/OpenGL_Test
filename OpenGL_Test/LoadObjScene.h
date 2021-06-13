#pragma once
#include "Scene.h"
#include "GouraudShadingEffect.h"
#include "Colors.h"

class LoadObjScene : public Scene
{
public:
	LoadObjScene(const char* file)
		:
		cube(graphics::LoadObjNormals<graphics::GouraudShadingEffect::Vertex>(std::string(file)))
	{
	}
	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window) override
	{
		gfx.Init(in_canvas);
		window = in_window;

		cubetransform.Translate({ 0.0f, 0.0f, 5.0f });
		gfx.effect.vertex_shader.BindTransform(cubetransform);
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

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			glm::vec3& vec = gfx.effect.vertex_shader.light_dir;
			float z = cosf(speed * dt) * vec.z - sinf(speed * dt) * vec.x;
			float x = sinf(speed * dt) * vec.z + cosf(speed * dt) * vec.x;

			vec.x = x;
			vec.z = z;
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			glm::vec3& vec = gfx.effect.vertex_shader.light_dir;
			float z = cosf(-speed * dt) * vec.z - sinf(-speed * dt) * vec.x;
			float x = sinf(-speed * dt) * vec.z + cosf(-speed * dt) * vec.x;

			vec.x = x;
			vec.z = z;
		}
	}


	void Draw() override
	{
		gfx.DrawMesh(cube);
	}

private:
	graphics::Graphics<graphics::GouraudShadingEffect> gfx;
	graphics::Mesh<graphics::GouraudShadingEffect::Vertex> cube;
	graphics::Transform cubetransform;
	GLFWwindow* window;
};