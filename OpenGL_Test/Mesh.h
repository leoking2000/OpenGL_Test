#pragma once
#include <vector>
#include "Transform.h"
#include "Colors.h"

struct Vertex
{
	glm::vec3 pos;
	graphics::Color color;
};

class Mesh
{
public:
	static Mesh MakeCube(float size);

	Mesh GetTransformMesh(const Transform& transform);
	void TransformMesh(const Transform& transform);
public:
	std::vector<Vertex> vartices;
	std::vector<uint32_t> indices;
};

