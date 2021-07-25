#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "Camera.h"
#include "GameObject.h"
#include <vector>

namespace Core
{
	class Light_Test : public Test
	{
	public:
		Light_Test()
			:
			proj(glm::perspective(glm::radians(45.0f), (float)GetWidth() / (float)GetHeight(), 0.1f, 500.0f)),
			lightMat("Shaders/OneColor.glsl"),
			woodMat("Shaders/Basic.glsl", "assets/wood_mc.png"),
			floorMat("Shaders/Basic.glsl", { 255, 127, 80, 255 }),
			light_color(1.0f, 1.0f, 1.0f),
			cube_mesh(Mesh::GenarateCube()),

			light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), *cube_mesh,lightMat,
				[&](const GameObject& gameObject)
				{
					gameObject.mat.shader.SetUniform("proj", proj);
					gameObject.mat.shader.SetUniform("view", Camera::Get().GetCameraView());
					gameObject.mat.shader.SetUniform("model", gameObject.GetModelMatrix());

					gameObject.mat.shader.SetUniform("u_object_color", light_color.x, light_color.y, light_color.z);
				})
		{

			auto SetUniform_Basic = [&](const GameObject& gameObject)
			{
				gameObject.mat.shader.SetUniform("proj", proj);
				gameObject.mat.shader.SetUniform("view", Camera::Get().GetCameraView());
				gameObject.mat.shader.SetUniform("model", gameObject.GetModelMatrix());

				gameObject.mat.shader.SetUniform("u_Tex", 0);

				gameObject.mat.shader.SetUniform("u_light_color", light_color.x, light_color.y, light_color.z);
				gameObject.mat.shader.SetUniform("u_light_pos", light.pos.x, light.pos.y, light.pos.z);

				glm::vec3 camPos = Camera::Get().pos;
				gameObject.mat.shader.SetUniform("u_cameraPos", camPos.x, camPos.y, camPos.z);
			};

			GameObjects.reserve(50);
			GameObjects.emplace_back(glm::vec3(  0.0f, -4.0f,  -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 1.0f, 50.0f), *cube_mesh, floorMat, SetUniform_Basic);
			GameObjects.emplace_back(glm::vec3(  5.0f,  1.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f, 5.0f, 10.0f), *cube_mesh, floorMat, SetUniform_Basic);
			GameObjects.emplace_back(glm::vec3(-14.0f,  1.0f, -12.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, *cube_mesh, woodMat, SetUniform_Basic);
			GameObjects.emplace_back(glm::vec3(-17.0f,  0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, *cube_mesh, woodMat, SetUniform_Basic);
			GameObjects.emplace_back(glm::vec3( 30.0f,  3.0f, -20.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, *cube_mesh, woodMat, SetUniform_Basic);
			GameObjects.emplace_back(glm::vec3(  5.0f,  2.0f, -11.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, *cube_mesh, woodMat, SetUniform_Basic);

		}

		void Update(float dt) override
		{
			float speed = 1.0f;

			Camera::Get().Update(dt);
		}

		void Draw() override
		{
			graphics::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			for (GameObject& GameObject : GameObjects)
			{
				GameObject.Draw();
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

		~Light_Test()
		{
			delete cube_mesh;
		}


	private:
		glm::mat4 proj;

		Mesh* cube_mesh;

		Matirial lightMat;
		Matirial woodMat;
		Matirial floorMat;

		glm::vec3 light_color;
		GameObject light;

		std::vector<GameObject> GameObjects;

		GLFWwindow* window = nullptr;
	};
}