#include "Vector3.h"
#include <cmath>
#include <assert.h>

Math::vec3::vec3()
    :
    vec2(0.0f, 0.0f), z(0.0f)
{
}

Math::vec3::vec3(float x, float y, float z)
    :
    vec2(x, y), z(z)
{
}

Math::vec3::vec3(const vec2& a, float z)
    :
    vec2(a.x, a.y), z(z)
{
}

Math::vec3 Math::vec3::zero()
{
    return vec3(0.0f, 0.0f, 0.0f);
}

Math::vec3 Math::vec3::up()
{
    return vec3(0.0f, 1.0f, 0.0f);
}

Math::vec3 Math::vec3::down()
{
    return vec3(0.0f, -1.0f, 0.0f);
}

Math::vec3 Math::vec3::right()
{
    return vec3(1.0f, 0.0f, 0.0f);
}

Math::vec3 Math::vec3::left()
{
    return vec3(-1.0f, 0.0f, 0.0f);
}

Math::vec3 Math::vec3::forward()
{
    return vec3(0.0f, 0.0f, 1.0f);
}

Math::vec3 Math::vec3::back()
{
    return vec3(0.0f, 0.0f, -1.0f);
}

float Math::vec3::distance(const vec3& a, const vec3& b)
{
    return (a - b).length();
}

float Math::vec3::dot(const vec3& a, const vec3& b)
{
    return a.x * b.x + a.y * b.y * a.z * b.z;
}

Math::vec3 Math::vec3::cross(const vec3& a, const vec3& b)
{
    return vec3(a.y * b.z - a.z * b.y , a.z * b.x - a.x * b.z , a.x * b.y - a.y * b.x);
}

Math::vec3 Math::vec3::reflect(const vec3& a, const vec3& normal)
{
    return a - 2.0f * normal * a.dot(normal);
}

float Math::vec3::sqrLength() const
{
    return this->dot(*this);
}

float Math::vec3::length() const
{
    return sqrtf(this->dot(*this));
}

Math::vec3 Math::vec3::normalized() const
{
    return *this / this->length();
}

bool Math::vec3::operator==(const vec3& a) const
{
    return x == a.x && y == a.y && z == a.z;
}

float Math::vec3::distance(const vec3& a) const
{
    return (*this - a).length();
}

float Math::vec3::dot(const vec3& a) const
{
    return a.x * x + a.y * y * a.z * z;
}

void Math::vec3::normalize()
{
    *this = *this / this->length();
}

Math::vec3& Math::vec3::operator+=(const vec3& a)
{
    x += a.x;
    y += a.y;
    z += a.z;

    return *this;
}

Math::vec3 Math::vec3::operator+(const vec3& a) const
{
    vec3 r(a.x, a.y, a.z);
    r += *this;

    return r;
}

Math::vec3& Math::vec3::operator-=(const vec3& a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;

    return *this;
}

Math::vec3 Math::vec3::operator-(const vec3& a) const
{
    vec3 r(a.x, a.y, a.z);
    r -= *this;

    return r;
}

Math::vec3 Math::vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

Math::vec3& Math::vec3::operator*=(float num)
{
    x *= num;
    y *= num;
    z *= num;

    return *this;
}

Math::vec3 Math::vec3::operator*(float num) const
{
    vec3 r(this->x, this->y, this->z);
    r *= num;

    return r;
}

Math::vec3& Math::vec3::operator/=(float num)
{
    x /= num;
    y /= num;
    z /= num;

    return *this;
}

Math::vec3 Math::vec3::operator/(float num) const
{
    vec3 r(this->x, this->y, this->z);
    r /= num;

    return r;
}

float& Math::vec3::operator[](int i)
{
    if (i == 0)
    {
        return x;
    }
    else if (i == 1)
    {
        return y;
    }
    else if (i == 2)
    {
        return z;
    }
    else
    {
        assert(false);
    }
}

Math::vec3 Math::operator*(float num, const vec3& a)
{
    vec3 r(a.x, a.y, a.z);
    r *= num;
    return r;
}

Math::vec3 Math::operator/(float num, const vec3& a)
{
    vec3 r(a.x, a.y, a.z);
    r *= num;
    return r;
}
