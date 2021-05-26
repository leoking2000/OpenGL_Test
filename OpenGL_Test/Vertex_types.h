#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Texture.h"

class Vertex
{
public:
	glm::vec3 pos;
	graphics::Color color;
};

class TexVertex
{
public:
	TexVertex(glm::vec3 pos, glm::vec2 TexCord, Texture* tex)
		:
		pos(pos),
		TexCord(TexCord),
		tex(tex)
	{

	}
	glm::vec3 pos;
	glm::vec2 TexCord;
	Texture* tex;
};