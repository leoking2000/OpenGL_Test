#pragma once
#include "math.h"

class VertexPC
{
public:
    glm::vec3 pos;
    glm::vec3 color;
public:
    VertexPC()
    {
        pos = glm::vec3(0.0f, 0.0f, 0.0f);
        color = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    VertexPC(const glm::vec3& in_pos)
    {
        pos = in_pos;
        color = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    VertexPC(glm::vec3 in_pos, glm::vec3 in_color)
    {
        pos = in_pos;
        color = in_color;
    }

    VertexPC(const glm::vec3& in_pos, const VertexPC& other)
    {
        pos = in_pos;
        color = other.color;
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
    VertexPC& operator*=(const glm::mat3x3& mat)
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

