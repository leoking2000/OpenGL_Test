#pragma once
#include "math.h"
#include "Mesh.h"
#include "Colors.h"
#include "DefaultVertexShader.h"

namespace graphics
{
	// solid color attribute taken from table in gs and not interpolated
	class SolidGeometryEffect
	{
	public:
		// the vertex type that will be input into the pipeline
		class Vertex
		{
		public:
			Vertex() = default;
			Vertex(const glm::vec3& pos)
				:
				pos(pos)
			{}
			Vertex(const glm::vec3& pos, const Vertex& src)
				:
				pos(pos)
			{}
			Vertex& operator+=(const Vertex& rhs)
			{
				pos += rhs.pos;
				return *this;
			}
			Vertex operator+(const Vertex& rhs) const
			{
				return Vertex(*this) += rhs;
			}
			Vertex& operator-=(const Vertex& rhs)
			{
				pos -= rhs.pos;
				return *this;
			}
			Vertex operator-(const Vertex& rhs) const
			{
				return Vertex(*this) -= rhs;
			}
			Vertex& operator*=(float rhs)
			{
				pos *= rhs;
				return *this;
			}
			Vertex& operator*=(const glm::mat3x3& mat)
			{
				pos = pos * mat;

				return *this;
			}
			Vertex operator*(float rhs) const
			{
				return Vertex(*this) *= rhs;
			}
			Vertex& operator/=(float rhs)
			{
				pos /= rhs;
				return *this;
			}
			Vertex operator/(float rhs) const
			{
				return Vertex(*this) /= rhs;
			}
		public:
			glm::vec3 pos;
			glm::vec3 light{ 0.0f,0.0f,0.0f };
		};
		// default vs rotates and translates vertices
		// does not touch attributes
		typedef DefaultVertexShader<Vertex> VertexShader;
		// gs colors vertices using their index from a table
		// every two triangles are colored from the same entry
		class GeometryShader
		{
		public:
			class Output
			{
			public:
				Output() = default;
				Output(const glm::vec3& pos)
					:
					pos(pos)
				{}
				Output(const glm::vec3& pos, const Output& src)
					:
					color(src.color),
					pos(pos)
				{}
				Output(const glm::vec3& pos, const Color& color)
					:
					color(color),
					pos(pos)
				{}
				Output& operator+=(const Output& rhs)
				{
					pos += rhs.pos;
					return *this;
				}
				Output operator+(const Output& rhs) const
				{
					return Output(*this) += rhs;
				}
				Output& operator-=(const Output& rhs)
				{
					pos -= rhs.pos;
					return *this;
				}
				Output operator-(const Output& rhs) const
				{
					return Output(*this) -= rhs;
				}
				Output& operator*=(float rhs)
				{
					pos *= rhs;
					return *this;
				}
				Output operator*(float rhs) const
				{
					return Output(*this) *= rhs;
				}
				Output& operator/=(float rhs)
				{
					pos /= rhs;
					return *this;
				}
				Output operator/(float rhs) const
				{
					return Output(*this) /= rhs;
				}
			public:
				glm::vec3 pos;
				Color color;
			};
		public:
			std::vector<Output> operator()(const VertexShader::Output& in0, const VertexShader::Output& in1, const VertexShader::Output& in2, size_t triangle_index) const
			{
				return{
					{ in0.pos,triangle_colors[triangle_index / 2] },
					{ in1.pos,triangle_colors[triangle_index / 2] },
					{ in2.pos,triangle_colors[triangle_index / 2] }
				};
			};
			void BindColors(std::vector<Color> colors)
			{
				triangle_colors = std::move(colors);
			}
		private:
			std::vector<Color> triangle_colors;
		};
		// invoked for each pixel of a triangle
		// takes an input of attributes that are the
		// result of interpolating vertex attributes
		// and outputs a color
		class PixelShader
		{
		public:
			template<class Input>
			Color operator()(const Input& in) const
			{
				return in.color;
			}
		};
	public:
		VertexShader vertex_shader;
		GeometryShader geometry_shader;
		PixelShader pixel_shader;
	};

	static Mesh<SolidGeometryEffect::Vertex> MakeCube_SolidGeometryEffect(float size)
	{
		Mesh<SolidGeometryEffect::Vertex> cube;

		const float s = size / 2.0f;

		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{ -s, -s, -s} });
		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{ -s,  s, -s} });
		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{  s,  s, -s} });
		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{  s, -s, -s} });
		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{  s,  s,  s} });
		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{  s, -s,  s} });
		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{ -s,  s,  s} });
		cube.vartices.emplace_back(SolidGeometryEffect::Vertex{ glm::vec3{ -s, -s,  s} });

		// Forward
		cube.indices.emplace_back(0);
		cube.indices.emplace_back(1);
		cube.indices.emplace_back(2);

		cube.indices.emplace_back(0);
		cube.indices.emplace_back(2);
		cube.indices.emplace_back(3);

		// EAST
		cube.indices.emplace_back(3);
		cube.indices.emplace_back(2);
		cube.indices.emplace_back(4);

		cube.indices.emplace_back(3);
		cube.indices.emplace_back(4);
		cube.indices.emplace_back(5);

		// BACK
		cube.indices.emplace_back(5);
		cube.indices.emplace_back(4);
		cube.indices.emplace_back(6);

		cube.indices.emplace_back(5);
		cube.indices.emplace_back(6);
		cube.indices.emplace_back(7);

		// WEST
		cube.indices.emplace_back(7);
		cube.indices.emplace_back(6);
		cube.indices.emplace_back(1);

		cube.indices.emplace_back(7);
		cube.indices.emplace_back(1);
		cube.indices.emplace_back(0);

		// NORTH
		cube.indices.emplace_back(1);
		cube.indices.emplace_back(6);
		cube.indices.emplace_back(4);

		cube.indices.emplace_back(1);
		cube.indices.emplace_back(4);
		cube.indices.emplace_back(2);

		// SOUTH
		cube.indices.emplace_back(5);
		cube.indices.emplace_back(7);
		cube.indices.emplace_back(0);

		cube.indices.emplace_back(5);
		cube.indices.emplace_back(0);
		cube.indices.emplace_back(3);

		return cube;
	}
}
