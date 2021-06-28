#pragma once
#include "math.h"

class VertexP
{
public:
	glm::vec3 pos;
public:
	VertexP() = default;
	VertexP(const glm::vec3 & pos)
		:
		pos(pos)
	{}
	VertexP(const glm::vec3 & pos, const VertexP & src)
		:
		pos(pos)
	{}
	VertexP& operator+=(const VertexP & rhs)
	{
		pos += rhs.pos;
		return *this;
	}
	VertexP operator+(const VertexP & rhs) const
	{
		return VertexP(*this) += rhs;
	}
	VertexP& operator-=(const VertexP & rhs)
	{
		pos -= rhs.pos;
		return *this;
	}
	VertexP operator-(const VertexP & rhs) const
	{
		return VertexP(*this) -= rhs;
	}
	VertexP& operator*=(float rhs)
	{
		pos *= rhs;
		return *this;
	}
	VertexP& operator*=(const glm::mat3x3 & mat)
	{
		pos = pos * mat;

		return *this;
	}
	VertexP operator*(float rhs) const
	{
		return VertexP(*this) *= rhs;
	}
	VertexP& operator/=(float rhs)
	{
		pos /= rhs;
		return *this;
	}
	VertexP operator/(float rhs) const
	{
		return VertexP(*this) /= rhs;
	}
};