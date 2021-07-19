#pragma once
#include "math.h"

class VertexPC
{
public:
    Math::vec4 pos;
    Math::vec3 color;
public:
    VertexPC()
        :
        pos(0.0f, 0.0f, 0.0f, 1.0f),
        color(0.0f, 0.0f, 0.0f)
    {
    }

    VertexPC(const Math::vec3& in_pos)
        :
        pos(in_pos, 1.0f),
        color(0.0f, 0.0f, 0.0f)
    {
    }

    VertexPC(Math::vec3 in_pos, Math::vec3 in_color)
        :
        pos(in_pos, 1.0f),
        color(in_color)
    {
    }

    VertexPC(const Math::vec3& in_pos, const VertexPC& other)
        :
        pos(in_pos, 1.0f),
        color(other.color)
    {
    }

    VertexPC& operator+=(const VertexPC& rhs)
    {
        pos += rhs.pos;
        color += rhs.color;

        return *this;
    }
    VertexPC operator+(const VertexPC& rhs) const
    {
        return VertexPC(*this) += rhs;
    }

    VertexPC& operator-=(const VertexPC& rhs)
    {
        pos -= rhs.pos;
        color -= rhs.color;

        return *this;
    }
    VertexPC operator-(const VertexPC& rhs) const
    {
        return VertexPC(*this) -= rhs;
    }

    VertexPC& operator*=(float rhs)
    {
        pos *= rhs;
        color *= rhs;

        return *this;
    }
    VertexPC& operator*=(const Math::mat4& mat)
    {
        pos = pos * mat;

        return *this;
    }
    VertexPC operator*(float rhs) const
    {
        return VertexPC(*this) *= rhs;
    }

    VertexPC& operator/=(float rhs)
    {
        pos /= rhs;
        color /= rhs;

        return *this;
    }
    VertexPC operator/(float rhs) const
    {
        VertexPC out(pos / rhs);
        out.color = color / rhs;

        return out;
    }
};

