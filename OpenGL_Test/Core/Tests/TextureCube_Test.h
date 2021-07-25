#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "Camera.h"
#include "Cube.h"
#include <vector>

namespace Core
{
	class TextureCube_Test : public Test
	{
	public:
		TextureCube_Test()
			:
			whiteMat("Shaders/Basic3DShader.glsl", Colors::White),
			woodMat("Shaders/Basic3DShader.glsl", "assets/wood_mc.png")
		{

			auto SetUniform = [](const Cube& cube)
			{
				cube.mat.shader.SetUniform("proj", glm::perspective(glm::radians(45.0f), (float)GetWidth() / (float)GetHeight(), 0.1f, 100.0f));
				cube.mat.shader.SetUniform("view", Camera::Get().GetCameraView());
				cube.mat.shader.SetUniform("model", cube.GetModelMatrix());

				cube.mat.shader.SetUniform("u_Tex", 0);
			};

			cubes.reserve(50);
			cubes.emplace_back(glm::vec3(  0.0f, -4.0f,  -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 1.0f, 50.0f), whiteMat, SetUniform);
			cubes.emplace_back(glm::vec3( 20.0f,  1.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f),  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3(-14.0f,  1.0f, -12.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f),  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3(-17.0f,  0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f),  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3( 30.0f,  3.0f, -20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f),  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3(  5.0f,  2.0f, -11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f),  woodMat, SetUniform);

			rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		void Update(float dt) override
		{
			float speed = 1.0f;

			Camera::Get().Update(dt);

			cubes[0].rotation = rotation;
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
		}

		void ImGui() override
		{

			ImGui::Begin("Rotation");
			ImGui::SliderFloat("X", &rotation.x, 0.0f, 2.0f * Math::PI);
			ImGui::SliderFloat("Y", &rotation.y, 0.0f, 2.0f * Math::PI);
			ImGui::SliderFloat("Z", &rotation.z, 0.0f, 2.0f * Math::PI);
			ImGui::End();


		}


	private:
		Matirial whiteMat;
		Matirial woodMat;
		std::vector<Cube> cubes;

		glm::vec3 rotation;
	
		GLFWwindow* window = nullptr;
	};
}