#pragma once
#include "Mesh.h"

namespace graphics
{
    template<class V>
    Mesh<V> MakeCube(float size)
    {
        Mesh<V> cube;

        const float s = size / 2.0f;

        std::vector<Math::vec3> vartices;

        // Forward
        vartices.emplace_back(-s,-s, -s);  // 0 0 
        vartices.emplace_back(-s, s, -s);  // 1 1
        vartices.emplace_back( s, s, -s);  // 2 2 
        vartices.emplace_back( s,-s, -s);  // 3 3

        cube.indices.emplace_back(0);
        cube.indices.emplace_back(1);
        cube.indices.emplace_back(2);

        cube.indices.emplace_back(0);
        cube.indices.emplace_back(2);
        cube.indices.emplace_back(3);

        // EAST
        vartices.emplace_back(s,  s, -s); // 2 4
        vartices.emplace_back(s, -s, -s); // 3 5
        vartices.emplace_back(s,  s,  s); // 4 6
        vartices.emplace_back(s, -s,  s); // 5 7

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(4);
        cube.indices.emplace_back(6);

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(6);
        cube.indices.emplace_back(7);

        // BACK
        vartices.emplace_back( s, s, s); // 4 8
        vartices.emplace_back( s,-s, s); // 5 9
        vartices.emplace_back(-s, s, s); // 6 10
        vartices.emplace_back(-s,-s, s); // 7 11

        cube.indices.emplace_back(9);
        cube.indices.emplace_back(8);
        cube.indices.emplace_back(10);

        cube.indices.emplace_back(9);
        cube.indices.emplace_back(10);
        cube.indices.emplace_back(11);

        // WEST
        vartices.emplace_back(-s,-s,-s); // 0 12
        vartices.emplace_back(-s, s,-s); // 1 13
        vartices.emplace_back(-s, s, s); // 6 14
        vartices.emplace_back(-s,-s, s); // 7 15

        cube.indices.emplace_back(15);
        cube.indices.emplace_back(14);
        cube.indices.emplace_back(13);

        cube.indices.emplace_back(15);
        cube.indices.emplace_back(13);
        cube.indices.emplace_back(12);

        // NORTH
        vartices.emplace_back(-s, s,-s); // 1 16
        vartices.emplace_back( s, s,-s); // 2 17
        vartices.emplace_back( s, s, s); // 4 18
        vartices.emplace_back(-s, s, s); // 6 19


        cube.indices.emplace_back(16);
        cube.indices.emplace_back(19);
        cube.indices.emplace_back(18);

        cube.indices.emplace_back(16);
        cube.indices.emplace_back(18);
        cube.indices.emplace_back(17);

        // SOUTH
        vartices.emplace_back(-s, -s,-s);// 0 20
        vartices.emplace_back( s, -s,-s);// 3 21
        vartices.emplace_back( s, -s, s);// 5 22
        vartices.emplace_back(-s, -s, s);// 7 23

        cube.indices.emplace_back(22);
        cube.indices.emplace_back(23);
        cube.indices.emplace_back(20);

        cube.indices.emplace_back(22);
        cube.indices.emplace_back(20);
        cube.indices.emplace_back(21);

        for (int i = 0; i < vartices.size(); i++)
        {
            cube.vartices.emplace_back(vartices[i]);
        }

        return cube;
    }

    
}

