#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Math
{
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

    template<class T>
    T Interpolate(const T& a, const T& b, float alpha)
    {
        return a + (b - a) * alpha;
    }
}
