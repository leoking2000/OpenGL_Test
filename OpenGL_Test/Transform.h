#pragma once
#include <glm/vec3.hpp>

class Transform
{
public:
	glm::vec3 pos;
	glm::vec3 rot;
public:
	void RotateZ(float rad);
	void RotateX(float rad);
	void RotateY(float rad);

	void Translate(const glm::vec3& offset);
};

