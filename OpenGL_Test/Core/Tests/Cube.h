#pragma once
#include "Core/graphics/Renderer.h"
#include "Material.h"
#include "Math/math.h"

#include <functional>

namespace Core
{
	class Cube
	{
	public:
		glm::vec3 pos;
		glm::vec3 rotation;
		glm::vec3 scale;

		const Matirial& mat;
	public:
		Cube(const glm::vec3& in_pos, const glm::vec3& in_rotation, const glm::vec3 in_scale, const Matirial& mat, std::function<void(const Cube&)> SetUniforms)
			:
			pos(in_pos),
			rotation(in_rotation),
			scale(in_scale),
			mat(mat),
			SetUniforms(SetUniforms)
		{
			Init();
		}

		Cube(const glm::vec3& in_pos, const Matirial& mat, std::function<void(const Cube&)> SetUniforms)
			:
			pos(in_pos),
			rotation(0.0f, 0.0f, 0.0f),
			scale(1.0f, 1.0f, 1.0f),
			mat(mat),
			SetUniforms(SetUniforms)
		{
			Init();
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

			graphics::Renderer::Draw(vertexArray, indexBuffer, mat.shader);
		}

	private:
		std::function<void(const Cube&)> SetUniforms;

		graphics::VertexArray vertexArray;
		graphics::VertexBuffer vertexBuffer;
		graphics::IndexBuffer indexBuffer;
	private:
		void Init()
		{
			vertexArray.Bind();

			float vertexs[] = {
				// pos                 // tex cord      // normal
				// Forward
				-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f,  0.0f, -1.0f, //0
				-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f,  0.0f, -1.0f, //1
				 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f,  0.0f, -1.0f, //2
				 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f,  0.0f, -1.0f, //3

				// EAST							  
				 0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    1.0f,  0.0f,  0.0f, //4
				 0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    1.0f,  0.0f,  0.0f, //5
				 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    1.0f,  0.0f,  0.0f, //6
				 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    1.0f,  0.0f,  0.0f, //7

				// BACK							  
				 0.5f,  0.5f,  0.5f,     0.0f, 1.0f,    0.0f,  0.0f,  1.0f, //8
				 0.5f, -0.5f,  0.5f,     0.0f, 0.0f,    0.0f,  0.0f,  1.0f, //9
				-0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    0.0f,  0.0f,  1.0f, //10
				-0.5f, -0.5f,  0.5f,     1.0f, 0.0f,    0.0f,  0.0f,  1.0f, //11

				// WEST							  
				-0.5f, -0.5f, -0.5f,     1.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //12
				-0.5f,  0.5f, -0.5f,     1.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //13
				-0.5f,  0.5f,  0.5f,     0.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //14
				-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //15

				// NORTH						  
				-0.5f,  0.5f, -0.5f,     0.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //16
				 0.5f,  0.5f, -0.5f,     0.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //17
				 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,    0.0f,  1.0f,  0.0f,  //18
				-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    0.0f,  1.0f,  0.0f,  //19

				// SOUTH						  
				-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,    0.0f, -1.0f,  0.0f,   //20
				 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,    0.0f, -1.0f,  0.0f,   //21
				 0.5f, -0.5f,  0.5f,     1.0f, 1.0f,    0.0f, -1.0f,  0.0f,   //22
				-0.5f, -0.5f,  0.5f,     0.0f, 1.0f,    0.0f, -1.0f,  0.0f    //23
			};

			vertexBuffer.Recreate(vertexs, sizeof(vertexs));

			graphics::ElementType arr[3] = { graphics::FLOAT3, graphics::FLOAT2, graphics::FLOAT3_N };
			graphics::Layout<3> layout(arr);
			vertexArray.AddBuffer(vertexBuffer, layout);

			// index buffer
			uint32_t indices[] = {
				// Forward
				0, 1, 2, /**/ 0, 2, 3,
				// EAST
				5, 4, 6, /**/ 5, 6, 7,
				// BACK
				9, 8, 10, /**/ 9, 10, 11,
				// WEST
				15, 14, 13, /**/ 15, 13, 12,
				// NORTH
				16, 19, 18, /**/ 16, 18, 17,
				// SOUTH
				22, 23, 20, /**/ 22, 20, 21
			};
			indexBuffer.Recreare(indices, 36);
		}
	};
}
