#pragma once
#include "math.h"

class VertexPN
{
public:
    glm::vec3 pos;
    glm::vec3 n;
public:
    VertexPN()
    {
        pos = glm::vec3(0.0f, 0.0f, 0.0f);
        n = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    VertexPN(const glm::vec3& in_pos)
    {
        pos = in_pos;
        n = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    VertexPN(glm::vec3 in_pos, glm::vec3 norm)
    {
        pos = in_pos;
        n = norm;
    }

    VertexPN(const glm::vec3& in_pos, const VertexPN& other)
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
    VertexPN& operator*=(const glm::mat3x3& mat)
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