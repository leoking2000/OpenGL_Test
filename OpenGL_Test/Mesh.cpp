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

    //cube.vartices.emplace_back(Vertex{{ -s, -s, -s},{255, 255, 255}}); // 0
    //cube.vartices.emplace_back(Vertex{{ -s,  s, -s},{255,   0,   0}}); // 1
    //cube.vartices.emplace_back(Vertex{{  s,  s, -s},{  0, 255,   0}}); // 2
    //cube.vartices.emplace_back(Vertex{{  s, -s, -s},{  0,   0, 255}}); // 3
    //cube.vartices.emplace_back(Vertex{{  s,  s,  s},{255, 255, 100}}); // 4
    //cube.vartices.emplace_back(Vertex{{  s, -s,  s},{100, 100, 100}}); // 5
    //cube.vartices.emplace_back(Vertex{{ -s,  s,  s},{  0,  40, 100}}); // 6
    //cube.vartices.emplace_back(Vertex{{ -s, -s,  s},{  0,   0, 100}}); // 7

    // Forward
    cube.vartices.emplace_back(Vertex{ { -s, -s, -s}, Colors::Green });// 0 0 
    cube.vartices.emplace_back(Vertex{ { -s,  s, -s}, Colors::Green });// 1 1
    cube.vartices.emplace_back(Vertex{ {  s,  s, -s}, Colors::Green });// 2 2 
    cube.vartices.emplace_back(Vertex{ {  s, -s, -s}, Colors::Green });// 3 3

    cube.indices.emplace_back(0);
    cube.indices.emplace_back(1);
    cube.indices.emplace_back(2);

    cube.indices.emplace_back(0);
    cube.indices.emplace_back(2);
    cube.indices.emplace_back(3);

    // EAST
    cube.vartices.emplace_back(Vertex{ {  s,  s, -s}, Colors::Red });// 2 4
    cube.vartices.emplace_back(Vertex{ {  s, -s, -s}, Colors::Red });// 3 5
    cube.vartices.emplace_back(Vertex{ {  s,  s,  s}, Colors::Red });// 4 6
    cube.vartices.emplace_back(Vertex{ {  s, -s,  s}, Colors::Red });// 5 7

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(4);
    cube.indices.emplace_back(6);

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(6);
    cube.indices.emplace_back(7);

    // BACK
    cube.vartices.emplace_back(Vertex{ {  s,  s,  s}, Colors::Blue }); // 4 8
    cube.vartices.emplace_back(Vertex{ {  s, -s,  s}, Colors::Blue }); // 5 9
    cube.vartices.emplace_back(Vertex{ { -s,  s,  s}, Colors::Blue }); // 6 10
    cube.vartices.emplace_back(Vertex{ { -s, -s,  s}, Colors::Blue }); // 7 11

    cube.indices.emplace_back(9);
    cube.indices.emplace_back(8);
    cube.indices.emplace_back(10);

    cube.indices.emplace_back(9);
    cube.indices.emplace_back(10);
    cube.indices.emplace_back(11);

    // WEST
    cube.vartices.emplace_back(Vertex{ { -s, -s, -s}, Colors::Gray }); // 0 12
    cube.vartices.emplace_back(Vertex{ { -s,  s, -s}, Colors::Gray }); // 1 13
    cube.vartices.emplace_back(Vertex{ { -s,  s,  s}, Colors::Gray  }); // 6 14
    cube.vartices.emplace_back(Vertex{ { -s, -s,  s}, Colors::Gray }); // 7 15

    cube.indices.emplace_back(15);
    cube.indices.emplace_back(14);
    cube.indices.emplace_back(13);

    cube.indices.emplace_back(15);
    cube.indices.emplace_back(13);
    cube.indices.emplace_back(12);

    // NORTH
    cube.vartices.emplace_back(Vertex{ { -s,  s, -s}, Colors::LightGray });// 1 16
    cube.vartices.emplace_back(Vertex{ {  s,  s, -s}, Colors::LightGray });// 2 17
    cube.vartices.emplace_back(Vertex{ {  s,  s,  s}, Colors::LightGray });// 4 18
    cube.vartices.emplace_back(Vertex{ { -s,  s,  s}, Colors::LightGray });// 6 19


    cube.indices.emplace_back(16);
    cube.indices.emplace_back(19);
    cube.indices.emplace_back(18);

    cube.indices.emplace_back(16);
    cube.indices.emplace_back(18);
    cube.indices.emplace_back(17);

    // SOUTH
    cube.vartices.emplace_back(Vertex{ { -s, -s, -s}, Colors::Cyan });// 0 20
    cube.vartices.emplace_back(Vertex{ {  s, -s, -s}, Colors::Cyan });// 3 21
    cube.vartices.emplace_back(Vertex{ {  s, -s,  s}, Colors::Cyan });// 5 22
    cube.vartices.emplace_back(Vertex{ { -s, -s,  s}, Colors::Cyan });// 7 23

    cube.indices.emplace_back(22);
    cube.indices.emplace_back(23);
    cube.indices.emplace_back(20);

    cube.indices.emplace_back(22);
    cube.indices.emplace_back(20);
    cube.indices.emplace_back(21);

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
        v.pos += transform.pos;
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

void Mesh::Translate(const glm::vec3& offset)
{
    transform.pos += offset;
}
