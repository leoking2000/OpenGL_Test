#pragma once
#include "Scene.h"
#include "GouraudPointEffect.h"
#include "OneColorEffect.h"
#include "Colors.h"

class LoadObjScene : public Scene
{
public:
	LoadObjScene(const char* file)
		:
		cube(graphics::LoadObjNormals<graphics::GouraudPointEffect::Vertex>(std::string(file))),
		sphere(graphics::LoadObj<graphics::OneColorEffect::Vertex>("assets/ccw_sphere.obj"))
	{
	}
	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window) override
	{
		gfx.Init(in_canvas);
		gfx_sphere.Init(in_canvas);
		window = in_window;

		cubetransform.Translate({ 0.0f, 0.0f, 3.0f });
		gfx.effect.vertex_shader.BindTransform(cubetransform);
		gfx.effect.pixel_shader.BindColor(Colors::Gray);

		spheretransform.Translate({ 0.0f, 0.0f, 1.0f });
		spheretransform.scale = 0.01f;
		gfx_sphere.effect.vertex_shader.BindTransform(spheretransform);
		gfx_sphere.effect.pixel_shader.BindColor(Colors::White);

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
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			cubetransform.Translate(glm::vec3(0.0f, 0.0f, speed) * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			cubetransform.Translate(-glm::vec3(0.0f, 0.0f, speed) * dt);
		}

		// light movement
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		{
			spheretransform.Translate(glm::vec3(0.0f, 0.0f, speed) * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		{
			spheretransform.Translate(-glm::vec3(0.0f, 0.0f, speed) * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		{
			spheretransform.Translate(-glm::vec3(speed, 0.0f, 0.0f) * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			spheretransform.Translate(glm::vec3(speed, 0.0f, 0.0f) * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		{
			spheretransform.Translate(glm::vec3(0.0f, speed, 0.0f) * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			spheretransform.Translate(-glm::vec3(0.0f, speed, 0.0f) * dt);
		}

		/*
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
		*/
		
		gfx.effect.vertex_shader.light_Pos = spheretransform.pos;
	}


	void Draw() override
	{
		gfx_sphere.DrawMesh(sphere);
		gfx.DrawMesh(cube);
	}

private:
	graphics::Graphics<graphics::GouraudPointEffect> gfx;
	graphics::Mesh<graphics::GouraudPointEffect::Vertex> cube;
	graphics::Transform cubetransform;

	graphics::Graphics<graphics::OneColorEffect> gfx_sphere;
	graphics::Mesh<graphics::OneColorEffect::Vertex> sphere;
	graphics::Transform spheretransform;


	GLFWwindow* window;
};