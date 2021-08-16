#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "Core/graphics/Camera.h"
#include "Core/graphics/GameObject.h"
#include "Core/graphics/Matirial/MatBasic.h"
#include <vector>

using namespace graphics;

namespace Core
{
	class Light_Test : public Test
	{
	public:
		Light_Test()
		{
			auto sphere_mesh = std::make_shared<graphics::Mesh>(*graphics::Mesh::GenarateSphere());
			auto cube_mesh = std::make_shared<graphics::Mesh>(*graphics::Mesh::GenarateCube());
			auto tea_mesh = std::make_shared<graphics::Mesh>(*graphics::Mesh::Load("assets/tea.obj"));
			auto monkey_mesh = std::make_shared<graphics::Mesh>(*graphics::Mesh::Load("assets/monkey.obj"));
			auto shuttle_mesh = std::make_shared<graphics::Mesh>(*graphics::Mesh::Load("assets/shuttle.obj"));

			graphics::MatBasic earthMat("assets/earth.jpg");
			graphics::MatBasic shuttleMat("assets/spstob_1.jpg");
			graphics::MatBasic tea_mat(glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f), 12.8f);
			graphics::MatBasic monkey_mat(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 51.2f);

			GameObjects.reserve(50);
			GameObjects.emplace_back(glm::vec3(-300.0f, -100.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 100.0f, sphere_mesh, std::make_unique<MatBasic>(earthMat));
			GameObjects.emplace_back(glm::vec3(-50.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), 40.0f, shuttle_mesh, std::make_unique<MatBasic>(shuttleMat));

			GameObjects.emplace_back(glm::vec3( 15.0f,  1.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f, 5.0f, 10.0f),
				cube_mesh, std::make_unique<MatBasic>(tea_mat));

			GameObjects.emplace_back(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, monkey_mesh, std::make_unique<MatBasic>(monkey_mat));

			GameObjects.emplace_back(glm::vec3(  0.0f, -6.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 1.0f, 50.0f), 
				cube_mesh, std::make_unique<MatBasic>(tea_mat));

			GameObjects.emplace_back(glm::vec3(  0.0f, -5.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, cube_mesh, std::make_unique<MatBasic>(monkey_mat));

			GameObjects.emplace_back(glm::vec3(-15.0f, 2.0f,  -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, tea_mesh, std::make_unique<MatBasic>(tea_mat));

			graphics::Renderer::MainCamera().pos = glm::vec3(0.0f, 1.0f, 40.0f);
		}

		void Update(float dt) override
		{

			graphics::Renderer::MainCamera().Update(cam_speed * dt);

			GameObjects[0].rotation.y = Math::wrap_angle(GameObjects[0].rotation.y + dt);
			GameObjects[3].rotation.y = Math::wrap_angle(GameObjects[3].rotation.y + dt);
		}

		void Draw() override
		{
			graphics::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			for (graphics::GameObject& GameObject : GameObjects)
			{
				GameObject.Draw();
			}
			Renderer::MainLight().Draw();
		}

		void ImGui() override
		{
			Renderer::MainLight().Imgui("Light");
		}

	private:
		float cam_speed = 5.0f;
		std::vector<graphics::GameObject> GameObjects;
	};
}