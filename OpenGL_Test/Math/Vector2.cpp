#include "Vector2.h"
#include <cmath>
#include <assert.h>

Math::vec2::vec2()
    :
    x(0.0f), y(0.0f)
{
}

Math::vec2::vec2(float x, float y)
    :
    x(x), y(y)
{
}

Math::vec2 Math::vec2::zero()
{
    return vec2(0.0f, 0.0f);
}

Math::vec2 Math::vec2::up()
{
    return vec2(0.0f, 1.0f);
}

Math::vec2 Math::vec2::down()
{
    return vec2(0.0f, -1.0f);
}

Math::vec2 Math::vec2::right()
{
    return vec2(1.0f, 0.0f);
}

Math::vec2 Math::vec2::left()
{
    return vec2(-1.0f, 0.0f);
}

float Math::vec2::distance(const vec2& a, const vec2& b)
{
    return (a - b).length();
}

float Math::vec2::dot(const vec2& a, const vec2& b)
{
    return a.x * b.x + a.y * b.y;
}

Math::vec2 Math::vec2::reflect(const vec2& a, const vec2& normal)
{
    return a - 2.0f * normal * a.dot(normal);
}

float Math::vec2::sqrLength() const
{
    return this->dot(*this);
}

float Math::vec2::length() const
{
    return sqrtf(this->dot(*this));
}

Math::vec2 Math::vec2::normalized() const
{
    return *this / this->length();
}

float& Math::vec2::operator[](int i)
{
    if (i == 0)
    {
        return x;
    }
    else if (i == 1)
    {
        return y;
    }
    else
    {
        assert(false);
    }
}

bool Math::vec2::operator==(const vec2& a) const
{
    return x == a.x && y == a.y;
}

float Math::vec2::distance(const vec2& a) const
{
    return (*this - a).length();
}

float Math::vec2::dot(const vec2& a) const
{
    return x * a.x + y * a.y;
}

void Math::vec2::normalize()
{
    *this = *this / this->length();
}

Math::vec2& Math::vec2::operator+=(const vec2& a)
{
    x += a.x;
    y += a.y;

    return *this;
}

Math::vec2 Math::vec2::operator+(const vec2& a) const
{
    vec2 r(this->x, this->y);
    r += *this;
    return r;
}

Math::vec2& Math::vec2::operator-=(const vec2& a)
{
    x -= a.x;
    y -= a.y;

    return *this;
}

Math::vec2 Math::vec2::operator-(const vec2& a) const
{
    vec2 r(this->x, this->y);
    r -= *this;
    return r;
}

Math::vec2& Math::vec2::operator*=(float num)
{
    x *= num;
    y *= num;

    return *this;
}

Math::vec2 Math::vec2::operator*(float num) const
{
    vec2 r(this->x, this->y);
    r *= num;
    return r;
}

Math::vec2& Math::vec2::operator/=(float num)
{
    x /= num;
    y /= num;

    return *this;
}

Math::vec2 Math::vec2::operator/(float num) const
{
    vec2 r(this->x, this->y);
    r /= num;
    return r;
}

Math::vec2 Math::operator*(float num, const vec2& a)
{
    vec2 r(a.x, a.y);
    r *= num;
    return r;
}

Math::vec2 Math::operator/(float num, const vec2& a)
{
    vec2 r(a.x, a.y);
    r /= num;
    return r;
}
