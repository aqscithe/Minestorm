#include <cmath>

#include "Vector2f.hpp"
#include "MathToolbox/maths.hpp"

Vector2f::Vector2f()
{}

Vector2f::Vector2f(float x_value, float y_value)
{
    m_x = x_value;
    m_y = y_value;
}

void          Vector2f::set(float x, float y)
{
    m_x = x;
    m_y = y;
}

Vector2f        Vector2f::fromAngle(float speed, float rotation)
{
    return { speed * cosf(rotation * maths::M_PI / 180.f), speed * sinf(rotation * maths::M_PI / 180.f) };
}

Vector2f     Vector2f::operator*(const Vector2f& other)
{
    return { m_x * other.m_x, m_y * other.m_y };
}

Vector2f     Vector2f::operator+(const Vector2f& other)
{
    return { m_x + other.m_x, m_y + other.m_y };
}

Vector2f     Vector2f::operator-(const Vector2f& other)
{
    return { m_x - other.m_x, m_y - other.m_y };
}

Vector2f&   Vector2f::operator+=(const Vector2f& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

Vector2f     Vector2f::operator*(float scalaire)
{
    return { m_x * scalaire, m_y * scalaire };
}

Vector2f&    Vector2f::operator*=(float scalaire)
{
    m_x *= scalaire;
    m_y *= scalaire;
    return *this;
}

bool Vector2f::operator==(const Vector2f& other)
{
    return m_x == other.m_x && m_y == other.m_y;
}

bool Vector2f::operator!=(const Vector2f& other)
{
    return !(*this == other);
}

/**
*   REVIEW:
*   Pour la stabilité et éviter les erreurs il est mieux de definir l'operator == et operator != qu'une seule fois.
* 
* 
*   bool Vector2f::operator==(const Vector2f& other)
*   {
*       return x == other.x && y == other.y;
*   }
* 
*   bool Vector2f::operator!=(const Vector2f& other)
*   {
*       return !(*this == other);
*   }
*/