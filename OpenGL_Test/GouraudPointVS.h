#pragma once
#include "math.h"
#include "Transform.h"
#include "Colors.h"
#include "VertexPC.h"

template<class Vertex>
class GouraudPointVS
{
public:
    typedef VertexPC Output;
public:
    glm::vec3 light_Pos{ 0.0f, 0.0f, 1.0f };
public:
    void BindTransform(graphics::Transform& transform_in)
    {
        transform = &transform_in;
    }
    Output operator()(const Vertex& in) const
    {
        Vertex trasformed(in.pos, in.n);
        graphics::Transform::TransformVertex(trasformed, *transform);

        const glm::vec3 delta = light_Pos - trasformed.pos;
        const float     dist  = glm::length(delta);
        const glm::vec3 dir   = glm::normalize(delta);

        const float i = 1.0f / (A * dist * dist + B * dist + C);

        glm::vec3 light = diffuse * i * std::max(0.0f, glm::dot(dir, trasformed.n));
        light.x = Math::clamp(light.x + ambient.x, 0.0f, 1.0f);
        light.y = Math::clamp(light.y + ambient.y, 0.0f, 1.0f);
        light.z = Math::clamp(light.z + ambient.z, 0.0f, 1.0f);

        Output out(trasformed.pos, light);

        return out;
    }
public:
    glm::vec3 diffuse{ 1.0f,1.0f,1.0f };
    glm::vec3 ambient{ 0.1f,0.1f,0.1f };
    float A = 1.0f; //2.619f;
    float B = 1.0f; //1.0f;
    float C = 1.0f; //0.382f;
private:
    graphics::Transform* transform;
};