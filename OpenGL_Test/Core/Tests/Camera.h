#pragma once
#include "Platform/MainWindow.h"
#include "GLFW/glfw3.h"
#include "Math/math.h"


namespace Core
{
	class Camera
	{
	public:

		glm::mat4 GetCameraView()
		{
			glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), dir);
			glm::vec3 up = glm::cross(dir, right);


			return glm::lookAt(pos, pos + dir, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Get().Update_dir(xpos, ypos);
		}

		void Update(float dt)
		{
			GLFWwindow* window = (GLFWwindow*)GetHandle();

			float move_speed = 10.0f;

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				pos = pos + dir * move_speed * dt;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				pos = pos - dir * move_speed * dt;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				pos += glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f))) * move_speed * dt;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				pos -= glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f))) * move_speed * dt;
			}

			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
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
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				glfwSetCursorPosCallback(window, nullptr);
			}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetCursorPosCallback(window, mouse_callback);
			}
		}

		static Camera& Get()
		{
			static Camera camera;

			return camera;
		}

	public:
		glm::vec3 pos;
		glm::vec3 dir;

		float yaw = -Math::PI / 2.0f;
		float pitch = 0.0f;

		bool mouseInput = false;
		bool x_press = false;
	private:
		Camera()
			:
			pos(0.0f, 0.0f, 10.0f),
			dir(0.0f, 0.0f, -1.0f)
		{
		}

		void Update_dir(double xpos, double ypos)
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

			float sensitivity = 0.005f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > Math::PI / 2.0f)
				pitch = Math::PI / 2.0f;
			if (pitch < -Math::PI / 2.0f)
				pitch = -Math::PI / 2.0f;

			glm::vec3 direction;
			direction.x = cos(yaw) * cos(pitch);
			direction.y = sin(pitch);
			direction.z = sin(yaw) * cos(pitch);
			dir = glm::normalize(direction);
		}

	};
}