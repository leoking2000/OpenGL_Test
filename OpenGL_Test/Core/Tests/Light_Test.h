#pragma once
#include "Test.h"
#include "Core/graphics/Renderer.h"

#include "../imgui/imgui.h"

#include "Core/graphics/Camera.h"
#include "Core/graphics/GameObject.h"
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
			earthMat("Shaders/Basic.glsl", "assets/earth.jpg"),
			floorMat("Shaders/Basic.glsl", { 255, 127, 80, 255 }),
			light_color(1.0f, 1.0f, 1.0f),
			cube_mesh(graphics::Mesh::GenarateCube()),
			sphere_mesh(graphics::Mesh::GenarateSphere()),
			tea_mesh(graphics::Mesh::Load("assets/tea.obj")),
			monkey_mesh(graphics::Mesh::Load("assets/monkey.obj")),

			light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), *cube_mesh,lightMat)
		{

			auto SetUniform_OneColor = [&](const graphics::GameObject& gameObject)
			{
				gameObject.mat.shader.SetUniform("proj", graphics::Renderer::proj);
				gameObject.mat.shader.SetUniform("view", cam.GetCameraView());
				gameObject.mat.shader.SetUniform("model", gameObject.GetModelMatrix());

				gameObject.mat.shader.SetUniform("u_object_color", light_color.x, light_color.y, light_color.z);
			};

			auto SetUniform_Basic = [&](const graphics::GameObject& gameObject)
			{
				gameObject.mat.shader.SetUniform("proj", graphics::Renderer::proj);
				gameObject.mat.shader.SetUniform("view", cam.GetCameraView());
				gameObject.mat.shader.SetUniform("model", gameObject.GetModelMatrix());

				gameObject.mat.shader.SetUniform("u_Tex", 0);

				gameObject.mat.shader.SetUniform("u_light_color", light_color.x, light_color.y, light_color.z);
				gameObject.mat.shader.SetUniform("u_light_pos", light.pos.x, light.pos.y, light.pos.z);

				gameObject.mat.shader.SetUniform("ambientStrength", ambientStrength);
				gameObject.mat.shader.SetUniform("specularStrength", specularStrength);
				gameObject.mat.shader.SetUniform("shininess", shininess);
			};

			lightMat.SetUniforms = SetUniform_OneColor;

			earthMat.SetUniforms = SetUniform_Basic;
			woodMat.SetUniforms = SetUniform_Basic;
			floorMat.SetUniforms = SetUniform_Basic;


			GameObjects.reserve(50);
			GameObjects.emplace_back(glm::vec3(  0.0f, -4.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 1.0f, 50.0f), *cube_mesh, floorMat);
			GameObjects.emplace_back(glm::vec3(  5.0f,  1.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f, 5.0f, 10.0f), *cube_mesh, floorMat);
			GameObjects.emplace_back(glm::vec3(  0.0f, -3.0f,   0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, *cube_mesh, woodMat);

			GameObjects.emplace_back(glm::vec3(-15.0f, 2.0f,    3.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, *sphere_mesh, earthMat); // 3

			GameObjects.emplace_back(glm::vec3(-15.0f, 2.0f,  -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, *tea_mesh, floorMat);
			GameObjects.emplace_back(glm::vec3( 0.0f, 0.0f,   -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, *monkey_mesh, floorMat);

			cam.pos = glm::vec3(0.0f, 0.0f, 40.0f);

		}

		void Update(float dt) override
		{
			float speed = 1.0f;

			cam.Update(dt);

			GameObjects[3].rotation.y = Math::wrap_angle(GameObjects[3].rotation.y + speed * dt);
		}

		void Draw() override
		{
			graphics::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			for (graphics::GameObject& GameObject : GameObjects)
			{
				GameObject.Draw();
			}

			light.Draw();
		}

		void ImGui() override
		{
			ImGui::Begin("Light");
			ImGui::SliderFloat("X Pos", &light.pos.x, -50.0f, 50.0f);
			ImGui::SliderFloat("Y Pos", &light.pos.y,  -3.0f, 50.0f);
			ImGui::SliderFloat("Z Pos", &light.pos.z, -50.0f, 50.0f);

			ImGui::ColorPicker4("light color", glm::value_ptr(light_color));

			ImGui::SliderFloat("Ambient", &ambientStrength, 0.0f, 0.5f);
			ImGui::SliderFloat("Specular", &specularStrength, 0.0f, 2.0f);
			ImGui::SliderFloat("shininess", &shininess, 0.0f, 64.0f);

			ImGui::End();
		}

		~Light_Test()
		{
			delete cube_mesh;
			delete sphere_mesh;
			delete tea_mesh;
			delete monkey_mesh;
		}


	private:
		graphics::Camera cam;

		graphics::Mesh* cube_mesh;
		graphics::Mesh* sphere_mesh;
		graphics::Mesh* tea_mesh;
		graphics::Mesh* monkey_mesh;

		graphics::Matirial lightMat;
		graphics::Matirial woodMat;
		graphics::Matirial earthMat;
		graphics::Matirial floorMat;

		glm::vec3 light_color;
		float ambientStrength = 0.05f;
		float specularStrength = 0.25f;
		float shininess = 64.0f;
		graphics::GameObject light;

		std::vector<graphics::GameObject> GameObjects;
	};
}