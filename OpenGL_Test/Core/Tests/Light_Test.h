#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "Core/graphics/Camera.h"
#include "Core/graphics/GameObject.h"
#include "Core/graphics/Matirial/MatBasic.h"
#include "Core/graphics/Matirial/MatBasicTex.h"
#include <vector>

using namespace graphics;

namespace Core
{
	class Light_Test : public Test
	{
	private:
		float cam_speed = 2.0f;
		std::vector<graphics::GameObject> gameObjects;


	public:
		Light_Test()
		{
			auto sphere_mesh = std::make_shared<graphics::Mesh>(graphics::Mesh::GenarateSphere());
			auto cube_mesh = std::make_shared<graphics::Mesh>(graphics::Mesh::GenarateCube());
			auto tea_mesh = std::make_shared<graphics::Mesh>(graphics::Mesh::Load("assets\\tea.obj"));
			auto monkey_mesh = std::make_shared<graphics::Mesh>(graphics::Mesh::Load("assets\\monkey.obj"));
			auto shuttle_mesh = std::make_shared<graphics::Mesh>(graphics::Mesh::Load("assets\\shuttle.obj"));
			auto sponza_mesh = std::make_shared<graphics::Mesh>(graphics::Mesh::Load("assets\\Sponza\\Sponza.obj"));

			MatBasic gold(0.83137255f, 0.68627451f, 0.21568627f);
			MatBasic darkOrange(1.0f, 0.54263566f, 0.0f);

			gameObjects.reserve(6);
			// space ship
			gameObjects.emplace_back(glm::vec3(0.0f,  3.0f, 5.0f) , glm::vec3(0.0f, 0.0f, 0.0f), 4.0f, shuttle_mesh,
				std::make_unique<MatBasicTex>("assets\\spstob_1.jpg"));

			// earth
			gameObjects.emplace_back(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, sphere_mesh,
				std::make_unique<MatBasicTex>("assets\\earth.jpg"));

			// monkey
			gameObjects.emplace_back(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, monkey_mesh, std::make_unique<MatBasic>(gold));

			// tea
			gameObjects.emplace_back(glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, tea_mesh, std::make_unique<MatBasic>(gold));

			// sponza
			gameObjects.emplace_back(glm::vec3(0.0f, -6.0f, 0.0f), glm::vec3(0.0f, Math::PI / 2.0f, 0.0f), 0.02f,
				sponza_mesh, std::make_unique<MatBasicTex>("assets\\spnza_bricks.tga"));

			graphics::Renderer::MainCamera().pos = glm::vec3(0.0f, 1.0f, 25.0f);
		}

		void Update(float dt) override
		{

			graphics::Renderer::MainCamera().Update(cam_speed * dt);

			gameObjects[1].rotation.y = Math::wrap_angle(gameObjects[1].rotation.y + dt);
			gameObjects[2].rotation.y = Math::wrap_angle(gameObjects[2].rotation.y + dt);
			gameObjects[3].rotation.y = Math::wrap_angle(gameObjects[3].rotation.y + dt);
		}

		void Draw() override
		{
			graphics::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			for (graphics::GameObject& GameObject : gameObjects)
			{
				GameObject.Draw();
			}
			Renderer::MainLight().Draw();
		}

		void ImGui() override
		{
			Renderer::MainLight().Imgui("Light");
		}
	};
}