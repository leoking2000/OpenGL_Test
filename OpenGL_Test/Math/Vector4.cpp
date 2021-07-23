#include "Vector4.h"
#include <assert.h>

Math::vec4::vec4()
    :
    vec3(0.0f, 0.0f, 0.0f), w(1.0f)
{
}

Math::vec4::vec4(float x, float y, float z, float w)
    :
    vec3(x, y, z), w(w)
{
}

Math::vec4::vec4(const vec3& a, float w)
    :
    vec3(a.x, a.y, a.z), w(w)
{
}

Math::vec4 Math::vec4::zero()
{
    return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

Math::vec4 Math::vec4::up()
{
    return vec4(0.0f, 1.0f, 0.0f, 0.0f);
}

Math::vec4 Math::vec4::down()
{
    return vec4(0.0f, -1.0f, 0.0f, 0.0f);
}

Math::vec4 Math::vec4::right()
{
    return vec4(1.0f, 0.0f, 0.0f, 0.0f);
}

Math::vec4 Math::vec4::left()
{
    return vec4(-1.0f, 0.0f, 0.0f, 0.0f);
}

Math::vec4 Math::vec4::forward()
{
    return vec4(0.0f, 0.0f, 1.0f, 0.0f);
}

Math::vec4 Math::vec4::back()
{
    return vec4(0.0f, 0.0f, -1.0f, 0.0f);
}

bool Math::vec4::operator==(const vec4& a) const
{
    return x == a.x && y == a.y && z == a.z && w == a.w;
}

Math::vec4& Math::vec4::operator+=(const vec4& a)
{
    x += a.x;
    y += a.y;
    z += a.z;
    w += a.w;

    return *this;
}

Math::vec4 Math::vec4::operator+(const vec4& a) const
{
    vec4 r(x + a.x, y + a.y, z + a.z, w + a.w);
    return r;
}

Math::vec4& Math::vec4::operator-=(const vec4& a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
    w -= a.w;

    return *this;
}

Math::vec4 Math::vec4::operator-(const vec4& a) const
{
    vec4 r(x - a.x, y - a.y, z - a.z, w - a.w);
    return r;
}

Math::vec4 Math::vec4::operator-() const
{
    return vec4(-x, -y, -z, -w);
}

Math::vec4& Math::vec4::operator*=(float num)
{
    x *= num;
    y *= num;
    z *= num;
    w *= num;

    return *this;
}

Math::vec4 Math::vec4::operator*(float num) const
{
    vec3 r(this->x * num, this->y * num, this->z * num);
    return r;
}

Math::vec4& Math::vec4::operator/=(float num)
{
    x /= num;
    y /= num;
    z /= num;
    w /= num;

    return *this;
}

Math::vec4 Math::vec4::operator/(float num) const
{
    vec3 r(this->x / num, this->y / num, this->z / num);

    return r;
}

float& Math::vec4::operator[](int i)
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
    else if (i == 3)
    {
        return w;
    }
    else
    {
        assert(false);
    }
}

Math::vec4 Math::operator*(float num, const vec4& a)
{
    vec3 r(a.x * num, a.y * num, a.z * num);
    return r;
}
