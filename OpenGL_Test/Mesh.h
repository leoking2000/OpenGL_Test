#pragma once
#include <vector>
#include "math.h"
#include "Transform.h"

namespace graphics
{
    template<class V>
    class Mesh
    {
    public:
        Mesh<V> GetTransformMesh(const Transform& transform) const
        {
            Mesh<V> out = *this; // copy

            out.TransformMesh(transform);

            return out;
        }
    public:
        std::vector<V> vartices;
        std::vector<uint64_t> indices;
    };
}

