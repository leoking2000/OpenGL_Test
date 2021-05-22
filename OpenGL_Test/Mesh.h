#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "Canvas.h"

struct Transform
{
	//glm::vec3 pos;
	glm::vec3 rot;
	//glm::vec3 scale;
};

struct Vertex
{
	glm::vec3 pos;
	graphics::Color color;
};

class Mesh
{
public:
	static Mesh MakeCube(float size);

	Mesh GetTransformMesh();

	void RotateZ(float rad);
	void RotateX(float rad);
	void RotateY(float rad);

public:
	std::vector<Vertex> vartices;
	std::vector<uint32_t> indices;

	Transform transform = {};
};

