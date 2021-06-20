#pragma once

#include "Vector2f.hpp"

namespace maths
{
    const float M_PI = 3.141592653589793238462643f;
    const float M_TAU = 6.283185307179586476925286f;

    inline float signf(float value)
    {
        if (value < 0.f)
            return -1.f;
        return 1.f;
    }

    inline Vector2f getPolyOrigin(const Vector2f& a, const Vector2f& b, const Vector2f& c)
    {
        return { (a.m_x + b.m_x + c.m_x) / 3.f, (a.m_y + b.m_y + c.m_y) / 3.f };
    } 

    inline Vector2f getPolyOrigin(const Vector2f& a, const Vector2f& b, const Vector2f& c, const Vector2f& d)
    {
        return { (a.m_x + b.m_x + c.m_x + d.m_x) / 4.f, (a.m_y + b.m_y + c.m_y + d.m_y) / 4.f };
    }
}