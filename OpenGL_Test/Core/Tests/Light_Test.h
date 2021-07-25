#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "Camera.h"
#include "Cube.h"
#include <vector>

namespace Core
{
	class Light_Test : public Test
	{
	public:
		Light_Test()
			:
			lightMat("Shaders/OneColor.glsl"),
			woodMat("Shaders/Basic.glsl", "assets/wood_mc.png"),
			floorMat("Shaders/Basic.glsl", {255, 127, 80, 255}),
			light_color(1.0f, 1.0f, 1.0f),

			light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), lightMat, 
				[&](const Cube& cube)
				{
					cube.mat.shader.SetUniform("proj", glm::perspective(glm::radians(45.0f), (float)GetWidth() / (float)GetHeight(), 0.1f, 100.0f));
					cube.mat.shader.SetUniform("view", Camera::Get().GetCameraView());
					cube.mat.shader.SetUniform("model", cube.GetModelMatrix());

					cube.mat.shader.SetUniform("u_object_color", light_color.x, light_color.y, light_color.z);
				})
		{

			auto SetUniform_Basic = [&](const Cube& cube)
			{
				cube.mat.shader.SetUniform("proj", glm::perspective(glm::radians(45.0f), (float)GetWidth() / (float)GetHeight(), 0.1f, 100.0f));
				cube.mat.shader.SetUniform("view", Camera::Get().GetCameraView());
				cube.mat.shader.SetUniform("model", cube.GetModelMatrix());

				cube.mat.shader.SetUniform("u_Tex", 0);

				cube.mat.shader.SetUniform("u_light_color", light_color.x, light_color.y, light_color.z);
				cube.mat.shader.SetUniform("u_light_pos", light.pos.x, light.pos.y, light.pos.z);

				glm::vec3 camPos = Camera::Get().pos;
				cube.mat.shader.SetUniform("u_cameraPos", camPos.x, camPos.y, camPos.z);
			};

			cubes.reserve(50);
			cubes.emplace_back(glm::vec3(  0.0f, -4.0f,  -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 1.0f, 50.0f), floorMat, SetUniform_Basic);
			cubes.emplace_back(glm::vec3(  5.0f,  1.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, woodMat, SetUniform_Basic);
			cubes.emplace_back(glm::vec3(-14.0f,  1.0f, -12.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, woodMat, SetUniform_Basic);
			cubes.emplace_back(glm::vec3(-17.0f,  0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, woodMat, SetUniform_Basic);
			cubes.emplace_back(glm::vec3( 30.0f,  3.0f, -20.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, woodMat, SetUniform_Basic);
			cubes.emplace_back(glm::vec3(  5.0f,  2.0f, -11.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, woodMat, SetUniform_Basic);

		}

		void Update(float dt) override
		{
			float speed = 1.0f;

			Camera::Get().Update(dt);
		}

		void Draw() override
		{
			graphics::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			glm::vec3 cubePositions[10] = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};

			for (Cube& cube : cubes)
			{
				cube.Draw();
			}

			light.Draw();
		}

		void ImGui() override
		{
			ImGui::Begin("Light");
			ImGui::SliderFloat("X Pos", &light.pos.x, -10.0f, 10.0f);
			ImGui::SliderFloat("Y Pos", &light.pos.y,  -3.0f, 10.0f);
			ImGui::SliderFloat("Z Pos", &light.pos.z, -10.0f, 10.0f);

			ImGui::ColorPicker4("light color", glm::value_ptr(light_color));
			ImGui::End();
		}


	private:
		Matirial lightMat;
		Matirial woodMat;
		Matirial floorMat;

		glm::vec3 light_color;
		Cube light;

		std::vector<Cube> cubes;

		GLFWwindow* window = nullptr;
	};
}