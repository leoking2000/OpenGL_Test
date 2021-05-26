#include "Make_Shape.h"

Mesh<Vertex> MakeCube(float size)
{
    Mesh<Vertex> cube;

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
    cube.vartices.emplace_back(Vertex{ { -s,  s,  s}, Colors::Gray }); // 6 14
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

Mesh<TexVertex> MakeCubeTex(float size, Texture& Forward
                                      , Texture& EAST
                                      , Texture& BACK
                                      , Texture& WEST
                                      , Texture& NORTH
                                      , Texture& SOUTH)
{
    Mesh<TexVertex> cube;

    const float s = size / 2.0f;

    // Forward
    cube.vartices.emplace_back(glm::vec3( -s, -s, -s), glm::vec2(0.0f, 0.0f), &Forward );// 0 0 
    cube.vartices.emplace_back(glm::vec3( -s,  s, -s), glm::vec2(1.0f, 0.0f), &Forward );// 1 1
    cube.vartices.emplace_back(glm::vec3(  s,  s, -s), glm::vec2(0.0f, 1.0f), &Forward );// 2 2 
    cube.vartices.emplace_back(glm::vec3(  s, -s, -s), glm::vec2(1.0f, 1.0f), &Forward );// 3 3

    cube.indices.emplace_back(0);
    cube.indices.emplace_back(1);
    cube.indices.emplace_back(2);

    cube.indices.emplace_back(0);
    cube.indices.emplace_back(2);
    cube.indices.emplace_back(3);

    // EAST
    cube.vartices.emplace_back(glm::vec3(  s,  s, -s), glm::vec2(0.0f, 0.0f), &EAST );// 2 4
    cube.vartices.emplace_back(glm::vec3(  s, -s, -s), glm::vec2(1.0f, 0.0f), &EAST );// 3 5
    cube.vartices.emplace_back(glm::vec3(  s,  s,  s), glm::vec2(0.0f, 1.0f), &EAST );// 4 6
    cube.vartices.emplace_back(glm::vec3(  s, -s,  s), glm::vec2(1.0f, 1.0f), &EAST );// 5 7

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(4);
    cube.indices.emplace_back(6);

    cube.indices.emplace_back(5);
    cube.indices.emplace_back(6);
    cube.indices.emplace_back(7);

    // BACK
    cube.vartices.emplace_back(glm::vec3(  s,  s,  s), glm::vec2{0.0f, 0.0f}, &BACK ); // 4 8
    cube.vartices.emplace_back(glm::vec3(  s, -s,  s), glm::vec2{1.0f, 0.0f}, &BACK ); // 5 9
    cube.vartices.emplace_back(glm::vec3( -s,  s,  s), glm::vec2{0.0f, 1.0f}, &BACK ); // 6 10
    cube.vartices.emplace_back(glm::vec3( -s, -s,  s), glm::vec2{1.0f, 1.0f}, &BACK ); // 7 11

    cube.indices.emplace_back(9);
    cube.indices.emplace_back(8);
    cube.indices.emplace_back(10);

    cube.indices.emplace_back(9);
    cube.indices.emplace_back(10);
    cube.indices.emplace_back(11);

    // WEST
    cube.vartices.emplace_back(glm::vec3( -s, -s, -s), glm::vec2(0.0f, 0.0f), &WEST ); // 0 12
    cube.vartices.emplace_back(glm::vec3( -s,  s, -s), glm::vec2(1.0f, 0.0f), &WEST ); // 1 13
    cube.vartices.emplace_back(glm::vec3( -s,  s,  s), glm::vec2(0.0f, 1.0f), &WEST ); // 6 14
    cube.vartices.emplace_back(glm::vec3( -s, -s,  s), glm::vec2(1.0f, 1.0f), &WEST ); // 7 15

    cube.indices.emplace_back(15);
    cube.indices.emplace_back(14);
    cube.indices.emplace_back(13);

    cube.indices.emplace_back(15);
    cube.indices.emplace_back(13);
    cube.indices.emplace_back(12);

    // NORTH
    cube.vartices.emplace_back(glm::vec3( -s,  s, -s), glm::vec2{0.0f, 0.0f}, &NORTH );// 1 16
    cube.vartices.emplace_back(glm::vec3(  s,  s, -s), glm::vec2{1.0f, 0.0f}, &NORTH );// 2 17
    cube.vartices.emplace_back(glm::vec3(  s,  s,  s), glm::vec2{0.0f, 1.0f}, &NORTH );// 4 18
    cube.vartices.emplace_back(glm::vec3( -s,  s,  s), glm::vec2{1.0f, 1.0f}, &NORTH );// 6 19


    cube.indices.emplace_back(16);
    cube.indices.emplace_back(19);
    cube.indices.emplace_back(18);

    cube.indices.emplace_back(16);
    cube.indices.emplace_back(18);
    cube.indices.emplace_back(17);

    // SOUTH
    cube.vartices.emplace_back(glm::vec3( -s, -s, -s), glm::vec2{0.0f, 0.0f}, &SOUTH );// 0 20
    cube.vartices.emplace_back(glm::vec3(  s, -s, -s), glm::vec2{1.0f, 0.0f}, &SOUTH );// 3 21
    cube.vartices.emplace_back(glm::vec3(  s, -s,  s), glm::vec2{0.0f, 1.0f}, &SOUTH );// 5 22
    cube.vartices.emplace_back(glm::vec3( -s, -s,  s), glm::vec2{1.0f, 1.0f}, &SOUTH );// 7 23

    cube.indices.emplace_back(22);
    cube.indices.emplace_back(23);
    cube.indices.emplace_back(20);

    cube.indices.emplace_back(22);
    cube.indices.emplace_back(20);
    cube.indices.emplace_back(21);

    return cube;
}


