#include "Mesh.h"
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template<typename T>
inline T wrap_angle(T theta)
{
    const T modded = fmod(theta, (T)2.0 * (T)PI_D);
    return (modded > (T)PI_D) ?
        (modded - (T)2.0 * (T)PI_D) :
        modded;
}

Mesh Mesh::MakeCube(float size)
{
    Mesh cube;

    const float s = size / 2.0f;

    cube.vartices.emplace_back(Vertex{{ -s, -s, -s},{255, 255, 255}});
    cube.vartices.emplace_back(Vertex{{ -s,  s, -s},{255,   0,   0}});
    cube.vartices.emplace_back(Vertex{{  s,  s, -s},{  0, 255,   0}});
    cube.vartices.emplace_back(Vertex{{  s, -s, -s},{  0,   0, 255}});
    cube.vartices.emplace_back(Vertex{{  s,  s,  s},{255, 255, 100}});
    cube.vartices.emplace_back(Vertex{{  s, -s,  s},{100, 100, 100}});
    cube.vartices.emplace_back(Vertex{{ -s,  s,  s},{  0,  40, 100}});
    cube.vartices.emplace_back(Vertex{{ -s, -s,  s},{  0,   0, 100}});

    // Forward
    cube.indices.emplace_back(0);
    cube.indices.emplace_back(1);
    cube.indices.emplace_back(2);

    cube.indices.emplace_back(0);
    cube.indices.emplace_back(2);
    cube.indices.emplace_back(3);

    // EAST
    cube.indices.emplace_back(3);
    cube.indices.emplace_back(2);
    cube.indices.emplace_back(4);

    cube.indices.emplace_back(3);
    cube.indices.emplace_back(4);
    cube.indices.emplace_back(5);

    // BACK
    cube.indices.emplace_back(5);
    cube.indices.emplace_back(4);
    cube.indices.emplace_back(6);

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(6);
    cube.indices.emplace_back(7);

    // WEST
    cube.indices.emplace_back(7);
    cube.indices.emplace_back(6);
    cube.indices.emplace_back(1);

    cube.indices.emplace_back(7);
    cube.indices.emplace_back(1);
    cube.indices.emplace_back(0);

    // NORTH
    cube.indices.emplace_back(1);
    cube.indices.emplace_back(6);
    cube.indices.emplace_back(4);

    cube.indices.emplace_back(1);
    cube.indices.emplace_back(4);
    cube.indices.emplace_back(2);

    // SOUTH
    cube.indices.emplace_back(5);
    cube.indices.emplace_back(7);
    cube.indices.emplace_back(0);

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(0);
    cube.indices.emplace_back(3);

    return cube;
}

Mesh Mesh::GetTransformMesh()
{
    Mesh out = *this; // copy

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

    for (auto& v : out.vartices)
    {
        glm::vec3 result = v.pos * rotation;
        v.pos = result;
        v.pos.z += 2;
    }

    return out;
}

void Mesh::RotateZ(float rad)
{
    transform.rot.z = wrap_angle(transform.rot.z + rad);
}

void Mesh::RotateX(float rad)
{
    transform.rot.x = wrap_angle(transform.rot.x + rad);
}

void Mesh::RotateY(float rad)
{
    transform.rot.y = wrap_angle(transform.rot.y + rad);
}
