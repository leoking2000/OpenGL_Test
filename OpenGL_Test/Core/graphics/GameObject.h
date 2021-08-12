#pragma once
#include "Matirial/Material.h"
#include "Mesh.h"

namespace graphics
{
	class GameObject
	{
	public:
		glm::vec3 pos;
		glm::vec3 rotation;
		glm::vec3 scale;

		Matirial& mat;
		Mesh& mesh;
	public:
		GameObject(const glm::vec3& in_pos, const glm::vec3& in_rotation, const glm::vec3& in_scale, Mesh* mesh, Matirial& mat)
			:
			pos(in_pos),
			rotation(in_rotation),
			scale(in_scale),
			mat(mat),
			mesh(*mesh)
		{
		}
		GameObject(const glm::vec3& in_pos, const glm::vec3& in_rotation, float in_scale, Mesh* mesh, Matirial& mat)
			:
			pos(in_pos),
			rotation(in_rotation),
			scale(in_scale, in_scale, in_scale),
			mat(mat),
			mesh(*mesh)
		{
		}

		GameObject(const glm::vec3& in_pos, Mesh* mesh, Matirial& mat)
			:
			pos(in_pos),
			rotation(0.0f, 0.0f, 0.0f),
			scale(1.0f, 1.0f, 1.0f),
			mat(mat),
			mesh(*mesh)
		{
		}

		glm::mat4 GetModelMatrix() const
		{
			glm::mat4 model(1.0f);

			model = glm::translate(model, pos);

			model = glm::scale(model, scale);

			model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			return model;
		}
	};
}
