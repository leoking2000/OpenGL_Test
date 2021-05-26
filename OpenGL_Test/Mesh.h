#pragma once
#include <vector>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Transform.h"
#include "Vertex_types.h"
#include "Colors.h"

template<class V>
class Mesh
{
public:
    Mesh<V> GetTransformMesh(const Transform& transform)
    {
        Mesh out = *this; // copy

        out.TransformMesh(transform);

        return out;
    }

    void TransformMesh(const Transform& transform)
    {
        float sin = std::sinf(transform.rot.z);
        float cos = std::cosf(transform.rot.z);
        float rZ[9] = { cos, -sin, 0.0f,
                        sin,  cos, 0.0f,
                       0.0f, 0.0f, 1.0f };

        sin = std::sinf(transform.rot.x);
        cos = std::cosf(transform.rot.x);
        float rX[9] = { 1.0f, 0.0f, 0.0f,
                        0.0f, cos,  -sin,
                        0.0f, sin,   cos };

        sin = std::sinf(transform.rot.y);
        cos = std::cosf(transform.rot.y);
        float rY[9] = { cos, 0.0f,  sin,
                       0.0f, 1.0f, 0.0f,
                       -sin, 0.0f,  cos };

        glm::mat3x3 rotation = glm::make_mat3x3(rZ) * glm::make_mat3x3(rX) * glm::make_mat3x3(rY);

        for (auto& v : vartices)
        {
            glm::vec3 result = v.pos * rotation;
            v.pos = result;
            v.pos += transform.pos;
        }
    }
public:
	std::vector<V> vartices;
	std::vector<uint32_t> indices;
};

