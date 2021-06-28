#pragma once
#include "math.h"
#include "Transform.h"
#include "Colors.h"
#include "VertexPC.h"

template<class Vertex>
class GouraudShadingVS
{
public:
    typedef VertexPC Output;
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