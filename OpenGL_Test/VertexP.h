#pragma once
#include "math.h"

class VertexP
{
public:
	Math::vec4 pos;
public:
	VertexP() = default;
	VertexP(const Math::vec3 & pos)
		:
		pos(pos)
	{}
	VertexP(const Math::vec3 & pos, const VertexP & src)
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
	VertexP& operator*=(const Math::mat4& mat)
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