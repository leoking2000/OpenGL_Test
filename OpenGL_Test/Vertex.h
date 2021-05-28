#pragma once
#include "math.h"
#include "Texture.h"

namespace graphics
{
	class Vertex
	{
	public:
		Vertex();
		Vertex(const Vertex& other);
		Vertex(const glm::vec3& in_pos, const glm::vec2& in_texCord);

		Vertex& operator+=(const Vertex& rhs);
		Vertex operator+(const Vertex& rhs) const;

		Vertex& operator-=(const Vertex& rhs);
		Vertex operator-(const Vertex& rhs) const;

		Vertex& operator*=(float rhs);
		Vertex operator*(float rhs) const;

		Vertex& operator/=(const Vertex& rhs);
		Vertex operator/(const Vertex& rhs) const;

		glm::vec3 pos;
		glm::vec2 texCord;
	};
}