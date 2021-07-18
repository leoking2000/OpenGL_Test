#include "Transform.h"
#include "math.h"


void graphics::Transform::RotateZ(float rad)
{
    rot.z = Math::wrap_angle(rot.z + rad);
}

void graphics::Transform::RotateX(float rad)
{
    rot.x = Math::wrap_angle(rot.x + rad);
}

void graphics::Transform::RotateY(float rad)
{
    rot.y = Math::wrap_angle(rot.y + rad);
}

void graphics::Transform::Translate(const Math::vec3& offset)
{
    pos += offset;
}