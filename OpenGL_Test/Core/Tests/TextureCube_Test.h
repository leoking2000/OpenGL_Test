#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "Core/graphics/Camera.h"
#include "GameObject.h"
#include <vector>

namespace Core
{
	class TextureCube_Test : public Test
	{
	public:
		TextureCube_Test()
			:
			cube_mesh(Mesh::GenarateCube()),
			whiteMat("Shaders/Basic3DShader.glsl", Colors::White),
			woodMat("Shaders/Basic3DShader.glsl", "assets/wood_mc.png")
		{

			auto SetUniform = [&](const GameObject& cube)
			{
				cube.mat.shader.SetUniform("proj", graphics::Renderer::proj);
				cube.mat.shader.SetUniform("view", cam.GetCameraView());
				cube.mat.shader.SetUniform("model", cube.GetModelMatrix());

				cube.mat.shader.SetUniform("u_Tex", 0);
			};

			cubes.reserve(50);
			cubes.emplace_back(glm::vec3(  0.0f, -4.0f,  -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 1.0f, 50.0f), *cube_mesh, whiteMat, SetUniform);
			cubes.emplace_back(glm::vec3( 20.0f,  1.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f), *cube_mesh,  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3(-14.0f,  1.0f, -12.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f), *cube_mesh,  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3(-17.0f,  0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f), *cube_mesh,  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3( 30.0f,  3.0f, -20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f), *cube_mesh,  woodMat, SetUniform);
			cubes.emplace_back(glm::vec3(  5.0f,  2.0f, -11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(  1.0f, 1.0f, 1.0f), *cube_mesh,  woodMat, SetUniform);

			rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		void Update(float dt) override
		{
			float speed = 1.0f;

			cam.Update(dt);

			cubes[0].rotation = rotation;
		}

		void Draw() override
		{
			graphics::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			for (GameObject& cube : cubes)
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

		~TextureCube_Test()
		{
			delete cube_mesh;
		}


	private:
		Mesh* cube_mesh;
		Matirial whiteMat;
		Matirial woodMat;

		graphics::Camera cam;

		std::vector<GameObject> cubes;

		glm::vec3 rotation;
	
		GLFWwindow* window = nullptr;
	};
}