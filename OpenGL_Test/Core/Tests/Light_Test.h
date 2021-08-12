#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "../imgui/imgui.h"

#include "Core/graphics/Camera.h"
#include "Core/graphics/GameObject.h"
#include "Core/graphics/Matirial/MatBasic.h"
#include <vector>

namespace Core
{
	class Light_Test : public Test
	{
	public:
		Light_Test()
			:
			tea_mat(glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f), 12.8f),
			monkey_mat(glm::vec3(0.24725f,0.1995f,	0.0745f), glm::vec3(	0.75164f,	0.60648f,	0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f),	51.2f),
			earthMat("assets/earth.jpg"),
			shuttleMat("assets/spstob_1.jpg"),

			cube_mesh(graphics::Mesh::GenarateCube()),
			sphere_mesh(graphics::Mesh::GenarateSphere()),
			tea_mesh(graphics::Mesh::Load("assets/tea.obj")),
			monkey_mesh(graphics::Mesh::Load("assets/monkey.obj")),
			shuttle_mesh(graphics::Mesh::Load("assets/shuttle.obj"))
		{

			GameObjects.reserve(50);
			GameObjects.emplace_back(glm::vec3(-300.0f, -100.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 100.0f, sphere_mesh, earthMat);
			GameObjects.emplace_back(glm::vec3(-50.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), 40.0f, shuttle_mesh, shuttleMat);

			GameObjects.emplace_back(glm::vec3( 15.0f,  1.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f, 5.0f, 10.0f), cube_mesh, tea_mat);
			GameObjects.emplace_back(glm::vec3(  0.0f, -6.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 1.0f, 50.0f), cube_mesh, tea_mat);
			GameObjects.emplace_back(glm::vec3(  0.0f, -5.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, cube_mesh, monkey_mat);

			GameObjects.emplace_back(glm::vec3(-15.0f, 2.0f,  -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, tea_mesh, tea_mat);
			GameObjects.emplace_back(glm::vec3( 0.0f, 0.0f,   -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, monkey_mesh, monkey_mat);

			graphics::Renderer::cam.pos = glm::vec3(0.0f, 1.0f, 40.0f);
		}

		void Update(float dt) override
		{

			graphics::Renderer::cam.Update(cam_speed * dt);

			GameObjects[0].rotation.y = Math::wrap_angle(GameObjects[0].rotation.y + dt);
		}

		void Draw() override
		{
			graphics::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			for (graphics::GameObject& GameObject : GameObjects)
			{
				graphics::Renderer::Draw(GameObject);
			}

		}

		void ImGui() override
		{

			ImGui::Begin("Space Shuttle");

			ImGui::SliderFloat("X Pos", &GameObjects[1].pos.x, -100.0f, 100.0f);
			ImGui::SliderFloat("Y Pos", &GameObjects[1].pos.y, -100.0f, 100.0f);
			ImGui::SliderFloat("Z Pos", &GameObjects[1].pos.z, -100.0f, 100.0f);

			ImGui::SliderFloat("X rot", &GameObjects[1].rotation.x, -2.0f * Math::PI, 2.0f * Math::PI);
			ImGui::SliderFloat("Y rot", &GameObjects[1].rotation.y, -2.0f * Math::PI, 2.0f * Math::PI);
			ImGui::SliderFloat("Z rot", &GameObjects[1].rotation.z, -2.0f * Math::PI, 2.0f * Math::PI);

			ImGui::End();
		}

		~Light_Test()
		{
			delete cube_mesh;
			delete sphere_mesh;
			delete tea_mesh;
			delete monkey_mesh;
			delete shuttle_mesh;
		}


	private:
		graphics::Mesh* cube_mesh;
		graphics::Mesh* sphere_mesh;
		graphics::Mesh* tea_mesh;
		graphics::Mesh* monkey_mesh;
		graphics::Mesh* shuttle_mesh;

		graphics::MatBasic tea_mat;
		graphics::MatBasic monkey_mat;
		//graphics::MatBasic floor_mat;
		//graphics::MatBasic wall_mat;

		graphics::MatBasic earthMat;
		graphics::MatBasic shuttleMat;

		 float cam_speed = 5.0f;

		std::vector<graphics::GameObject> GameObjects;
	};
}