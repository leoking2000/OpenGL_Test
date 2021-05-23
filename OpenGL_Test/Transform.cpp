#include "Transform.h"

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template<typename T>
inline T wrap_angle(T theta)
{
    const T modded = fmod(theta, (T)2.0 * (T)PI_D);
    return (modded > (T)PI_D) ?
        (modded - (T)2.0 * (T)PI_D) :
        modded;
}

void Transform::RotateZ(float rad)
{
    rot.z = wrap_angle(rot.z + rad);
}

void Transform::RotateX(float rad)
{
    rot.x = wrap_angle(rot.x + rad);
}

void Transform::RotateY(float rad)
{
    rot.y = wrap_angle(rot.y + rad);
}

void Transform::Translate(const glm::vec3& offset)
{
    pos += offset;
}