#include "Camera.h"

graphics::Camera::Camera()
	:
	pos(0.0f, 0.0f, 0.0f),
	dir(0.0f, 0.0f, -1.0f)
{
}

graphics::Camera::Camera(const glm::vec3& in_pos, const glm::vec3& in_dir)
	:
	pos(in_pos),
	dir(glm::normalize(in_dir))
{
}

glm::mat4 graphics::Camera::GetCameraView()
{
	return glm::lookAt(pos, pos + dir, glm::vec3(0.0f, 1.0f, 0.0f));
}

void graphics::Camera::Update(float dt)
{
	float move_speed = 10.0f;

	if (Platform::KeyIsPress(Platform::KEY_W))
	{
		pos = pos + dir * move_speed * dt;
	}
	if (Platform::KeyIsPress(Platform::KEY_S))
	{
		pos = pos - dir * move_speed * dt;
	}

	if (Platform::KeyIsPress(Platform::KEY_D))
	{
		pos += glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f))) * move_speed * dt;
	}
	if (Platform::KeyIsPress(Platform::KEY_A))
	{
		pos -= glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f))) * move_speed * dt;
	}

	if (Platform::KeyIsPress(Platform::KEY_X))
	{
		if (x_press == false)
		{
			mouseInput = !mouseInput;
			x_press = true;
		}
	}
	else
	{
		x_press = false;
	}

	if (mouseInput == false)
	{
		Platform::SetMouseVisibility(true);
	}
	else
	{
		Platform::SetMouseVisibility(false);
		Update_dir(Platform::GetMouseX(), Platform::GetMouseY(), dt);
	}
}

void graphics::Camera::Update_dir(double xpos, double ypos, float dt)
{
	static bool firstMouse = true;
	static double lastX;
	static double lastY;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f * dt;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > Math::PI / 2.0f)
		pitch = Math::PI / 2.0f;
	if (pitch < -Math::PI / 2.0f)
		pitch = -Math::PI / 2.0f;

	glm::vec3 direction;
	direction.x = glm::cos(yaw) * glm::cos(pitch);
	direction.y = glm::sin(pitch);
	direction.z = glm::sin(yaw) * glm::cos(pitch);
	dir = glm::normalize(direction);
}




