#pragma once
#include "Renderer.h"
#include "../imgui/imgui.h"
#include <memory>

namespace graphics
{
	class GameObject
	{
	public:
		glm::vec3 pos;
		glm::vec3 rotation;
		glm::vec3 scale;
	public:
		GameObject(const glm::vec3& in_pos, const glm::vec3& in_rotation, const glm::vec3& in_scale, std::shared_ptr<Mesh> mesh, std::unique_ptr<Matirial> mat)
			:
			pos(in_pos),
			rotation(in_rotation),
			scale(in_scale),
			mat(std::move(mat)),
			mesh(std::move(mesh))
		{
		}
		GameObject(const glm::vec3& in_pos, const glm::vec3& in_rotation, float in_scale, std::shared_ptr<Mesh> mesh, std::unique_ptr<Matirial> mat)
			:
			pos(in_pos),
			rotation(in_rotation),
			scale(in_scale, in_scale, in_scale),
			mat(std::move(mat)),
			mesh(std::move(mesh))
		{
		}

		GameObject(const glm::vec3& in_pos, std::shared_ptr<Mesh> mesh, std::unique_ptr<Matirial> mat)
			:
			pos(in_pos),
			rotation(0.0f, 0.0f, 0.0f),
			scale(1.0f, 1.0f, 1.0f),
			mat(std::move(mat)),
			mesh(std::move(mesh))
		{
		}

		void Draw()
		{
			mat->SetUniforms(GetModelMatrix());

			Renderer::Draw(mat.get(), *mesh);
		}

		Matirial& GetMatirial()
		{
			return *mat;
		}
	
	private:
		glm::mat4 GetModelMatrix() const
		{
			glm::mat4 model(1.0f);

			model = glm::translate(model, pos);

			model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			model = glm::scale(model, scale);

			return model;
		}
	private:
		std::unique_ptr<Matirial> mat;
		std::shared_ptr<Mesh> mesh;
	};
}
