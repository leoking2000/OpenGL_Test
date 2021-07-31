#pragma once
#include "MainWindow.h"
#include "leo_math.h"


namespace graphics
{
	class Camera
	{
	public:
		glm::vec3 pos;
		glm::vec3 dir;

		float yaw = -Math::PI / 2.0f;
		float pitch = 0.0f;

		bool mouseInput = false;
		bool x_press = false;
	public:
		Camera();

		Camera(const glm::vec3& in_pos, const glm::vec3& in_dir);

		glm::mat4 GetCameraView();

		void Update(float dt);

	private:
		void Update_dir(double xpos, double ypos, float dt);

	};
}