#pragma once

#include <random>

#include "Mine.hpp"
#include "MathToolbox/geo_calculs.hpp"
#include "MathToolbox//maths.hpp"

Mine::Mine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId)
{
	m_typeId = typeId;
	m_sizeId = sizeId;
	m_position = startPos;
	m_texture = texture;
	m_scale = m_scales[sizeId];
	m_sourceRec.width = texture.width;
	m_sourceRec.height = texture.height;
	m_destRec.width = m_texture.width * m_scale;
	m_destRec.height = m_texture.height * m_scale;
	m_origin = { m_texture.width * m_scale / 2, m_texture.height * m_scale / 2 };

	std::random_device generator;
	m_angularSpeed = std::uniform_int_distribution<int>{ 3, 10 }(generator) * 0.1f;
}


Mine::Mine(const Mine& other)
{
	*this = other;
}

void Mine::operator=(const Mine& other)
{
	m_targetPos = other.m_targetPos;
	m_hasTarget = other.m_hasTarget;
	m_followDelay = other.m_followDelay;

	int speedsCount = sizeof(m_mineSpeeds) / sizeof(m_mineSpeeds[0]);
	for (int i = 0; i < speedsCount; ++i)
		m_mineSpeeds[i] = other.m_mineSpeeds[i];

	int scalesSize = sizeof(m_scales) / sizeof(m_scales[0]);
	for (int i = 0; i < scalesSize; ++i)
		m_scales[i] = other.m_scales[i];

	int typeCount = sizeof(m_points) / sizeof(m_points[0]);
	int pointCount = sizeof(m_points[0]) / sizeof(m_points[0][0]);
	for (int i = 0; i < typeCount; ++i)
		for (int j = 0; j < pointCount; ++j)
			m_points[i][j] = other.m_points[i][j];

	Entity::equalize(other);
}

void Mine::locateTarget(std::vector<Coordinates>& positions)
{
	if (positions.size() > 0)
	{
		m_direction = v2::getDirShortestDistance(positions, this->getPosition(), m_targetPos);
		m_hasTarget = true;
	}
	else
	{
		m_hasTarget = false;
	}
	
}


void	Mine::update(float elapsedTime)
{
	if (m_typeId == 2 || m_typeId == 3)
	{
		if (m_hasTarget )
		{
			m_speed = m_direction * m_mineSpeeds[m_sizeId];
		}
		else if (m_hasTarget && m_followDelay > 0.f)
		{
			m_followDelay -= elapsedTime;
			m_speed = { 0.f, 0.f };
		}
		else
		{
			m_speed = { 0.f, 0.f };
			m_followDelay = 0.1f;
		}
	}
	

	auto distance = m_speed * elapsedTime;
	m_position += distance;
	m_rotation = angleClamp(m_rotation + m_angularSpeed);

	m_destRec.x = this->getPosition().getX();
	m_destRec.y = this->getPosition().getY();

	if (m_collisionsActive)
	{
		switch (m_typeId)
		{
			case 2:
				updateMagPolys();
				break;
			default:
				break;
		}
		Entity::updateAABB();
		Entity::updatePolys();
	}
}

void Mine::updateMagPolys()
{
	convexPolygon triangle1;
	triangle1.vertices.push_back(m_shape.vertices.at(0));
	triangle1.vertices.push_back(m_shape.vertices.at(1));
	triangle1.vertices.push_back(m_shape.vertices.at(7));
	triangle1.local.angle = m_rotation;
	triangle1.local.origin = maths::getPolyOrigin(triangle1.vertices.at(0), triangle1.vertices.at(1), triangle1.vertices.at(2));
	m_polygons.push_back(triangle1);

	convexPolygon triangle2;
	triangle2.vertices.push_back(m_shape.vertices.at(1));
	triangle2.vertices.push_back(m_shape.vertices.at(2));
	triangle2.vertices.push_back(m_shape.vertices.at(3));
	triangle2.local.angle = m_rotation;
	triangle2.local.origin = maths::getPolyOrigin(triangle2.vertices.at(0), triangle2.vertices.at(1), triangle2.vertices.at(2));
	m_polygons.push_back(triangle2);

	convexPolygon triangle3;
	triangle3.vertices.push_back(m_shape.vertices.at(3));
	triangle3.vertices.push_back(m_shape.vertices.at(4));
	triangle3.vertices.push_back(m_shape.vertices.at(5));
	triangle3.local.angle = m_rotation;
	triangle3.local.origin = maths::getPolyOrigin(triangle3.vertices.at(0), triangle3.vertices.at(1), triangle3.vertices.at(2));
	m_polygons.push_back(triangle3);

	convexPolygon triangle4;
	triangle4.vertices.push_back(m_shape.vertices.at(5));
	triangle4.vertices.push_back(m_shape.vertices.at(6));
	triangle4.vertices.push_back(m_shape.vertices.at(7));
	triangle4.local.angle = m_rotation;
	triangle4.local.origin = maths::getPolyOrigin(triangle4.vertices.at(0), triangle4.vertices.at(1), triangle4.vertices.at(2));
	m_polygons.push_back(triangle4);
}
