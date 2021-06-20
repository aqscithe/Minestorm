#include <iostream>
#include <cmath>
#include <algorithm>

#include "Coordinates.hpp"
#include "MathToolbox/maths.hpp"
#include "MathToolbox/geo_calculs.hpp"

int Coordinates::m_spaceLength = 0;
int Coordinates::m_spaceHeight = 0;
int Coordinates::m_bottomOffset = 0;
int Coordinates::m_topOffset = 0;
int Coordinates::m_leftOffset = 0;
int Coordinates::m_rightOffset = 0;
int Coordinates::m_maxScreenX = 0;
int	Coordinates::m_minScreenX = 0;
int	Coordinates::m_maxScreenY = 0;
int	Coordinates::m_minScreenY = 0;
Vector2f Coordinates::m_worldOrigin = { 0.f, 0.f };

Coordinates::Coordinates() {
    if (m_spaceLength == 0 || m_spaceHeight == 0) {
        std::cerr << "Attention: A coordinat was created before initializing the screen space!" << std::endl;
    }
}

Coordinates::Coordinates(float px, float py) : m_x(px), m_y(py) 
{
    recalculate();
}

void Coordinates::operator+=(Vector2f const& vector) {
    m_x += vector.m_x;
    m_y += vector.m_y;
    recalculate();
}

void Coordinates::initializeSpace(int length, int height)
{
    if ((m_spaceLength != 0) || (m_spaceHeight != 0))
    {
        std::cerr << "Attention: A coordinat was created before initializing the screen space." << std::endl;
    }
    m_spaceLength = length;
    m_spaceHeight = height;
    m_bottomOffset = 90;
    m_topOffset = 60;
    m_leftOffset = 60;
    m_rightOffset = 60;
    m_maxScreenX = m_spaceLength - m_rightOffset;
    m_minScreenX = m_leftOffset;
    m_maxScreenY = m_spaceHeight - m_bottomOffset;
    m_minScreenY = m_topOffset;
    m_worldOrigin = { (float)m_leftOffset, (float)m_bottomOffset };
}

void Coordinates::recalculate()
{
    while (m_x > m_maxScreenX) 
    {
        m_x -= m_spaceLength - (m_rightOffset + m_leftOffset);
    }
    while (m_x < m_minScreenX) 
    {
        m_x += m_spaceLength - (m_rightOffset + m_leftOffset);
    }
    while (m_y > m_maxScreenY) 
    {
        m_y -= m_spaceHeight - (m_topOffset + m_bottomOffset);
    }
    while (m_y < m_minScreenY) 
    {
        m_y += m_spaceHeight - (m_topOffset + m_bottomOffset);
    }
}
  
float Coordinates::calculateDistance(Coordinates const& autre) const
{
    auto delta = Vector2f{ std::min({abs(m_x - autre.m_x), abs(m_x - autre.m_x - m_spaceLength), m_x - autre.m_x + m_spaceHeight}),
        std::min({abs(m_y - autre.m_y), abs(m_y - autre.m_y - m_spaceHeight), m_y - autre.m_y + m_spaceHeight}) };
    return v2::vecMagnitude(delta);
}
    




