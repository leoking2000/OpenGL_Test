#pragma once
#include "math.h"
#include "Transform.h"
#include "Colors.h"

template<class Vertex>
class GouraudShadingVS
{
public:
    class Output
    {
    public:
        glm::vec3 pos;
        glm::vec3 color;
    public:
        Output()
        {
            pos = glm::vec3(0.0f, 0.0f, 0.0f);
            color = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        Output(const glm::vec3& in_pos)
        {
            pos = in_pos;
            color = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        Output(glm::vec3 in_pos, glm::vec3 in_color)
        {
            pos = in_pos;
            color = in_color;
        }

        Output(const glm::vec3& in_pos, const Output& other)
        {
            pos = in_pos;
            color = other.color;
        }

        Output& operator+=(const Output& rhs)
        {
            pos += rhs.pos;
            color += rhs.color;

            return *this;
        }
        Output operator+(const Output& rhs) const
        {
            return Output(*this) += rhs;
        }

        Output& operator-=(const Output& rhs)
        {
            pos -= rhs.pos;
            color -= rhs.color;

            return *this;
        }
        Output operator-(const Output& rhs) const
        {
            return Output(*this) -= rhs;
        }

        Output& operator*=(float rhs)
        {
            pos *= rhs;
            color *= rhs;

            return *this;
        }
        Output& operator*=(const glm::mat3x3& mat)
        {
            pos = pos * mat;

            return *this;
        }
        Output operator*(float rhs) const
        {
            return Output(*this) *= rhs;
        }

        Output& operator/=(float rhs)
        {
            pos /= rhs;
            color /= rhs;

            return *this;
        }
        Output operator/(float rhs) const
        {
            Output out(pos / rhs);
            out.color = color / rhs;

            return out;
        }
    };
public:
    void BindTransform(graphics::Transform& transform_in)
    {
        transform = &transform_in;
    }
    Output operator()(const Vertex& in) const
    {
        Vertex trasformed(in.pos, in.n);
        graphics::Transform::TransformVertex(trasformed, *transform);

        glm::vec3 light = diffuse * std::max(0.0f, -glm::dot(light_dir, trasformed.n));
        light.x = Math::clamp(light.x + ambient.x, 0.0f, 1.0f);
        light.y = Math::clamp(light.y + ambient.y, 0.0f, 1.0f);
        light.z = Math::clamp(light.z + ambient.z, 0.0f, 1.0f);

        Output out(trasformed.pos, light);

        return out;
    }
public:
    glm::vec3 light_dir{ 0.0f, 0.0f, 1.0f };

    glm::vec3 diffuse{ 1.0f,1.0f,1.0f };
    glm::vec3 ambient{ 0.1f,0.1f,0.1f };
private:
    graphics::Transform* transform;
};