#pragma once
#include <vector>
#include "math.h"
#include "Transform.h"

#include <fstream>

namespace graphics
{
    template<class V>
    class Mesh
    {
    public:
        std::vector<V> vartices;
        std::vector<uint64_t> indices;
    };

    template<class V>
    Mesh<V> LoadObj(const char* filename)
    {
        Mesh<V> cube;




        return cube;
    }
}

