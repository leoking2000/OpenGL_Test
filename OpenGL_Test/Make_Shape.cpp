#include "Make_Shape.h"

graphics::Mesh graphics::MakeCube(float size)
{
    graphics::Mesh cube;

    const float s = size / 2.0f;

    // Forward
    cube.vartices.emplace_back(glm::vec3( -s, -s, -s), glm::vec2(0.0f, 0.0f));// 0 0 
    cube.vartices.emplace_back(glm::vec3( -s,  s, -s), glm::vec2(1.0f, 0.0f));// 1 1
    cube.vartices.emplace_back(glm::vec3(  s,  s, -s), glm::vec2(0.0f, 1.0f));// 2 2 
    cube.vartices.emplace_back(glm::vec3(  s, -s, -s), glm::vec2(1.0f, 1.0f));// 3 3

    cube.indices.emplace_back(0);
    cube.indices.emplace_back(1);
    cube.indices.emplace_back(2);

    cube.indices.emplace_back(0);
    cube.indices.emplace_back(2);
    cube.indices.emplace_back(3);

    // EAST
    cube.vartices.emplace_back(glm::vec3(  s,  s, -s), glm::vec2(0.0f, 0.0f));// 2 4
    cube.vartices.emplace_back(glm::vec3(  s, -s, -s), glm::vec2(1.0f, 0.0f));// 3 5
    cube.vartices.emplace_back(glm::vec3(  s,  s,  s), glm::vec2(0.0f, 1.0f));// 4 6
    cube.vartices.emplace_back(glm::vec3(  s, -s,  s), glm::vec2(1.0f, 1.0f));// 5 7

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(4);
    cube.indices.emplace_back(6);

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(6);
    cube.indices.emplace_back(7);

    // BACK
    cube.vartices.emplace_back(glm::vec3(  s,  s,  s), glm::vec2{0.0f, 0.0f}); // 4 8
    cube.vartices.emplace_back(glm::vec3(  s, -s,  s), glm::vec2{1.0f, 0.0f}); // 5 9
    cube.vartices.emplace_back(glm::vec3( -s,  s,  s), glm::vec2{0.0f, 1.0f}); // 6 10
    cube.vartices.emplace_back(glm::vec3( -s, -s,  s), glm::vec2{1.0f, 1.0f}); // 7 11

    cube.indices.emplace_back(9);
    cube.indices.emplace_back(8);
    cube.indices.emplace_back(10);

    cube.indices.emplace_back(9);
    cube.indices.emplace_back(10);
    cube.indices.emplace_back(11);

    // WEST
    cube.vartices.emplace_back(glm::vec3( -s, -s, -s), glm::vec2(0.0f, 0.0f)); // 0 12
    cube.vartices.emplace_back(glm::vec3( -s,  s, -s), glm::vec2(1.0f, 0.0f)); // 1 13
    cube.vartices.emplace_back(glm::vec3( -s,  s,  s), glm::vec2(0.0f, 1.0f)); // 6 14
    cube.vartices.emplace_back(glm::vec3( -s, -s,  s), glm::vec2(1.0f, 1.0f)); // 7 15

    cube.indices.emplace_back(15);
    cube.indices.emplace_back(14);
    cube.indices.emplace_back(13);

    cube.indices.emplace_back(15);
    cube.indices.emplace_back(13);
    cube.indices.emplace_back(12);

    // NORTH
    cube.vartices.emplace_back(glm::vec3( -s,  s, -s), glm::vec2{0.0f, 0.0f});// 1 16
    cube.vartices.emplace_back(glm::vec3(  s,  s, -s), glm::vec2{1.0f, 0.0f});// 2 17
    cube.vartices.emplace_back(glm::vec3(  s,  s,  s), glm::vec2{0.0f, 1.0f});// 4 18
    cube.vartices.emplace_back(glm::vec3( -s,  s,  s), glm::vec2{1.0f, 1.0f});// 6 19


    cube.indices.emplace_back(16);
    cube.indices.emplace_back(19);
    cube.indices.emplace_back(18);

    cube.indices.emplace_back(16);
    cube.indices.emplace_back(18);
    cube.indices.emplace_back(17);

    // SOUTH
    cube.vartices.emplace_back(glm::vec3( -s, -s, -s), glm::vec2{0.0f, 0.0f});// 0 20
    cube.vartices.emplace_back(glm::vec3(  s, -s, -s), glm::vec2{1.0f, 0.0f});// 3 21
    cube.vartices.emplace_back(glm::vec3(  s, -s,  s), glm::vec2{0.0f, 1.0f});// 5 22
    cube.vartices.emplace_back(glm::vec3( -s, -s,  s), glm::vec2{1.0f, 1.0f});// 7 23

    cube.indices.emplace_back(22);
    cube.indices.emplace_back(23);
    cube.indices.emplace_back(20);

    cube.indices.emplace_back(22);
    cube.indices.emplace_back(20);
    cube.indices.emplace_back(21);

    return cube;
}


