#pragma once
#include "Core/graphics/Renderer.h"
#include "Material.h"
#include "Math/math.h"
#include "Mesh.h"

#include <functional>

namespace graphics
{
	class GameObject
	{
	public:
		glm::vec3 pos;
		glm::vec3 rotation;
		glm::vec3 scale;

		const Matirial& mat;
		const Mesh& mesh;
	public:
		GameObject(const glm::vec3& in_pos, const glm::vec3& in_rotation, const glm::vec3& in_scale, const Mesh& mesh, const Matirial& mat, std::function<void(const GameObject&)> SetUniforms)
			:
			pos(in_pos),
			rotation(in_rotation),
			scale(in_scale),
			mat(mat),
			SetUniforms(SetUniforms),
			mesh(mesh)
		{
		}
		GameObject(const glm::vec3& in_pos, const glm::vec3& in_rotation, float in_scale, const Mesh& mesh, const Matirial& mat, std::function<void(const GameObject&)> SetUniforms)
			:
			pos(in_pos),
			rotation(in_rotation),
			scale(in_scale, in_scale, in_scale),
			mat(mat),
			SetUniforms(SetUniforms),
			mesh(mesh)
		{
		}

		GameObject(const glm::vec3& in_pos, const Mesh& mesh, const Matirial& mat, std::function<void(const GameObject&)> SetUniforms)
			:
			pos(in_pos),
			rotation(0.0f, 0.0f, 0.0f),
			scale(1.0f, 1.0f, 1.0f),
			mat(mat),
			SetUniforms(SetUniforms),
			mesh(mesh)
		{
		}

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

		void Draw() const
		{
			mat.Bind();

			SetUniforms(*this);

			graphics::Renderer::Draw(mesh.vertexArray, mesh.indexBuffer, mat.shader);
		}

	private:
		std::function<void(const GameObject&)> SetUniforms;

	};
}
