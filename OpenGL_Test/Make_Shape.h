#pragma once
#include "Mesh.h"
#include "Texture.h"

Mesh<Vertex> MakeCube(float size);
Mesh<TexVertex> MakeCubeTex(float size, Texture& Forward
    , Texture& EAST
    , Texture& BACK
    , Texture& WEST
    , Texture& NORTH
    , Texture& SOUTH);

