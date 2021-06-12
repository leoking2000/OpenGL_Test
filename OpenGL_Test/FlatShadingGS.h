#pragma once
#include "math.h"
#include <vector>
#include "Colors.h"

template<class Vertex>
class FlatShadingGS
{
public:
    typedef typename Vertex Output;
public:
    std::vector<Output> operator()(Vertex& in0, Vertex& in1, Vertex& in2, size_t triangle_index) const
    {

        glm::vec3 n = glm::normalize(glm::cross(in1.pos - in0.pos, in2.pos - in0.pos));

        glm::vec3 light = diffuse * std::max(0.0f, -glm::dot(light_dir, n));


        light.x = Math::clamp(light.x + ambient.x, 0.0f, 1.0f);
        light.y = Math::clamp(light.y + ambient.y, 0.0f, 1.0f);
        light.z = Math::clamp(light.z + ambient.z, 0.0f, 1.0f);

        in0.light = light;
        in1.light = light;
        in2.light = light;

        return{ in0,in1,in2 };
    }
public:
    glm::vec3 light_dir{ 0.0f, 0.0f, 1.0f };

    glm::vec3 diffuse{ 1.0f,1.0f,1.0f };
    glm::vec3 ambient{ 0.1f,0.1f,0.1f };
};