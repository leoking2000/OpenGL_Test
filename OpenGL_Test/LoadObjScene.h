#pragma once
#include "Scene.h"
#include "PhongPointEffect.h"
#include "OneColorEffect.h"
#include "Colors.h"

class LoadObjScene : public Scene
{
public:
	LoadObjScene(const char* file, float scale)
		:
		mesh(graphics::LoadObjNormals<graphics::PhongPointEffect::Vertex>(std::string(file))),
		sphere(graphics::LoadObj<graphics::OneColorEffect::Vertex>("assets/ccw_sphere.obj")),
		scale(scale)
	{
	}
	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window) override
	{
		gfx.Init(in_canvas);
		gfx_sphere.Init(in_canvas);
		window = in_window;

		meshtransform.Translate({ 0.0f, 0.0f, 3.0f });
		meshtransform.scale = scale;
		gfx.effect.vertex_shader.BindTransform(meshtransform);
		gfx.effect.pixel_shader.BindColor(Colors::Gray);

		spheretransform.Translate({ 0.0f, 0.0f, 1.0f });
		spheretransform.scale = 0.01f;
		gfx_sphere.effect.vertex_shader.BindTransform(spheretransform);
		gfx_sphere.effect.pixel_shader.BindColor(Colors::White);

	}

	void Update(float dt) override
	{
		float speed = 1.0f;

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			meshtransform.RotateX(speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			meshtransform.RotateX(-speed * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			meshtransform.RotateY(speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			meshtransform.RotateY(-speed * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			meshtransform.RotateZ(speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			meshtransform.RotateZ(-speed * dt);
		}

		// fordward 
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			meshtransform.Translate(glm::vec3(0.0f, 0.0f, speed) * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			meshtransform.Translate(-glm::vec3(0.0f, 0.0f, speed) * dt);
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
		
		gfx.effect.pixel_shader.light_Pos = spheretransform.pos;
	}


	void Draw() override
	{
		gfx_sphere.DrawMesh(sphere);
		gfx.DrawMesh(mesh);
	}

private:
	graphics::Graphics<graphics::PhongPointEffect> gfx;
	graphics::Mesh<graphics::PhongPointEffect::Vertex> mesh;
	graphics::Transform meshtransform;

	graphics::Graphics<graphics::OneColorEffect> gfx_sphere;
	graphics::Mesh<graphics::OneColorEffect::Vertex> sphere;
	graphics::Transform spheretransform;

	float scale = 1.0f;

	GLFWwindow* window;
};