#pragma once
#include "math.h"

class VertexPN
{
public:
    Math::vec3 pos;
    Math::vec3 n;
public:
    VertexPN()
    {
        pos = Math::vec3(0.0f, 0.0f, 0.0f);
        n = Math::vec3(0.0f, 0.0f, 0.0f);
    }

    VertexPN(const Math::vec3& in_pos)
    {
        pos = in_pos;
        n = Math::vec3(0.0f, 0.0f, 0.0f);
    }

    VertexPN(Math::vec3 in_pos, Math::vec3 norm)
    {
        pos = in_pos;
        n = norm;
    }

    VertexPN(const Math::vec3& in_pos, const VertexPN& other)
    {
        pos = in_pos;
        n = other.n;
    }

    VertexPN& operator+=(const VertexPN& rhs)
    {
        pos += rhs.pos;

        return *this;
    }
    VertexPN operator+(const VertexPN& rhs) const
    {
        return VertexPN(*this) += rhs;
    }

    VertexPN& operator-=(const VertexPN& rhs)
    {
        pos -= rhs.pos;

        return *this;
    }
    VertexPN operator-(const VertexPN& rhs) const
    {
        return VertexPN(*this) -= rhs;
    }

    VertexPN& operator*=(float rhs)
    {
        pos *= rhs;

        return *this;
    }
    VertexPN& operator*=(const Math::mat3& mat)
    {
        pos = pos * mat;
        n = n * mat;


        return *this;
    }
    VertexPN operator*(float rhs) const
    {
        return VertexPN(*this) *= rhs;
    }

    VertexPN& operator/=(float rhs)
    {
        pos /= rhs;

        return *this;
    }
    VertexPN operator/(float rhs) const
    {
        VertexPN out(pos / rhs);

        return out;
    }
};