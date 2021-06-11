#include "CubeWithTexture.h"

CubeWithTexture::CubeWithTexture(const char* path_texture)
	:
	tex(path_texture),
	cube(graphics::MakeCube_TextureEffect(1))
{
}

void CubeWithTexture::Init(graphics::Canvas* in_canvas, GLFWwindow* in_window)
{
	gfx.Init(in_canvas);
	window = in_window;

	cubetransform.Translate({ 0.0f, 0.0f, 2.0f });
	gfx.effect.vertex_shader.BindTransform(cubetransform);
	gfx.effect.pixel_shader.BindTexture(tex);
}

void CubeWithTexture::Update(float dt)
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
		glm::vec3& vec = gfx.effect.geometry_shader.light_dir;
		float z = cosf(speed * dt) * vec.z - sinf(speed * dt) * vec.x;
		float x = sinf(speed * dt) * vec.z + cosf(speed * dt) * vec.x;

		vec.x = x;
		vec.z = z;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glm::vec3& vec = gfx.effect.geometry_shader.light_dir;
		float z = cosf(-speed * dt) * vec.z - sinf(-speed * dt) * vec.x;
		float x = sinf(-speed * dt) * vec.z + cosf(-speed * dt) * vec.x;

		vec.x = x;
		vec.z = z;
	}

}

void CubeWithTexture::Draw()
{
	gfx.DrawMesh(cube);
}
