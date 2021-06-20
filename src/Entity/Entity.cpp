#pragma once

#include <iostream>
#include <string>

#include "Entity.hpp"
#include "MathToolbox/geo_calculs.hpp"
#include "MathToolbox/maths.hpp"

Entity::Entity()
{}

Entity::~Entity()
{}

void	Entity::equalize(const Entity& other)
{
	this->m_typeId = other.m_typeId;
	this->m_sizeId = other.m_sizeId;
	this->m_angularSpeed = other.m_angularSpeed;
	this->m_direction = other.m_direction;
	this->m_speed = other.m_speed;
	this->m_origin = other.m_origin;
	this->m_rotation = other.m_rotation;
	this->m_scale = other.m_scale;
	this->m_position = other.m_position;
	this->m_texture = other.m_texture;
	this->m_sourceRec = other.m_sourceRec;
	this->m_destRec = other.m_destRec;
	this->m_bodyColor = other.m_bodyColor;
	this->m_collisionLines = other.m_collisionLines;
	this->m_collisionBox = other.m_collisionBox;
	this->m_shape = other.m_shape;
	this->m_collisionsActive = other.m_collisionsActive;
	this->m_colliding = other.m_colliding;
	this->m_markedForDeletion = other.m_markedForDeletion;
	this->m_polygons = other.m_polygons;
}

bool	Entity::operator==(int deleteCode)
{
	return (m_markedForDeletion && deleteCode == -99);
}

void	Entity::updateCollision(bool collisionHandled)
{
	if (m_colliding && collisionHandled)
	{
		m_markedForDeletion = true;
	}
	m_collisionLines = m_colliding ? GREEN : RED;
	m_colliding = false;
}

void	Entity::updateTemp(bool collided)
{
	if (!m_colliding)
		m_colliding = collided;
}


void	Entity::draw(bool collisionLinesActive)
{
	DrawTexturePro(m_texture, m_sourceRec, m_destRec, { m_origin.m_x, m_origin.m_y }, m_rotation, m_bodyColor);

	if (m_collisionsActive && collisionLinesActive)
	{
		// Draw AABB
		for (int i = 0; i < m_collisionBox.vertices.size(); ++i)
		{

			Vector2f vertex1 = m_collisionBox.vertices.at(i);
			Vector2f vertex2 = m_collisionBox.vertices.at((i + 1) % m_collisionBox.vertices.size());
			DrawLine((int)vertex1.m_x, (int)vertex1.m_y, (int)vertex2.m_x, (int)vertex2.m_y, m_collisionLines);
		}

		// Draw Polygons
		for (convexPolygon& poly : m_polygons)
		{
			for (int i = 0; i < poly.vertices.size(); ++i)
			{
				
				Vector2f vertex1 = poly.vertices.at(i);
				Vector2f vertex2 = poly.vertices.at((i + 1) % poly.vertices.size());
				DrawLine((int)vertex1.m_x, (int)vertex1.m_y, (int)vertex2.m_x, (int)vertex2.m_y, YELLOW);
			}
		}
	}
}

void	Entity::update(float elapsedTime)
{
	Vector2f pos = { m_position.getX(), m_position.getY() };
	m_direction = v2::getVector({ pos.m_x, pos.m_y }, { pos.m_x + m_destRec.height / 2 * cosf((m_rotation - 90.f)*maths::M_PI / 180.f), pos.m_y + m_destRec.height / 2 * sinf((m_rotation - 90.f)*maths::M_PI / 180.f) });

	auto distance = m_speed * elapsedTime;
	m_position += distance;
	m_rotation = angleClamp(m_rotation + m_angularSpeed);

	m_destRec.x = this->getPosition().getX();
	m_destRec.y = this->getPosition().getY();

	if (m_collisionsActive)
	{
		Entity::updateAABB();
		Entity::updatePolys();
	}
		
}

void	Entity::updateAABB()
{
	// Get new origin
	m_collisionBox.local.origin = convertPointGameScreen({ m_destRec.x, m_destRec.y });
	m_shape.local.origin = m_collisionBox.local.origin;
	m_shape.local.angle = m_rotation;


	// Find the axes
	Vector2f x_axis = { m_collisionBox.local.origin.m_x + 2.f * m_destRec.width, m_collisionBox.local.origin.m_y };
	Vector2f y_axis = { m_collisionBox.local.origin.m_x, m_collisionBox.local.origin.m_y - 2.f * m_destRec.height };


	// local referential
	m_collisionBox.local.vector_i = v2::getUnitVector(v2::getVector(m_collisionBox.local.origin, convertPointGameScreen(x_axis)));
	m_collisionBox.local.vector_j = v2::getUnitVector(v2::getVector(m_collisionBox.local.origin, convertPointGameScreen(y_axis)));
	m_collisionBox.local.angle = m_rotation;


	// find width and height of AABB based on vertex locations
	range x_axe = { 0.f, 0.f };
	range y_axe = { 0.f, 0.f };
	for (int i = 0; i < m_shape.vertices.size(); ++i)
	{
		Vector2f vertex = { (m_shape.vertices.at(i).m_x * m_scale + m_destRec.x) , (m_shape.vertices.at(i).m_y * m_scale + m_destRec.y) };
		vertex = rotatePoint(convertPointGameScreen(m_collisionBox.local.origin), vertex, m_shape.local.angle);
		if (i == 0)
		{
			x_axe = { vertex.m_x, vertex.m_x };
			y_axe = { vertex.m_y, vertex.m_y };
		}
		else
		{
			x_axe.min = minf(x_axe.min, vertex.m_x);
			x_axe.max = maxf(x_axe.max, vertex.m_x);
			y_axe.min = minf(y_axe.min, vertex.m_y);
			y_axe.max = maxf(y_axe.max, vertex.m_y);
		}
	}
	
	// update AABB vertices
	m_collisionBox.vertices.clear();
	m_collisionBox.vertices.push_back({ x_axe.min  , y_axe.max });
	m_collisionBox.vertices.push_back({ x_axe.max , y_axe.max });
	m_collisionBox.vertices.push_back({ x_axe.max , y_axe.min });
	m_collisionBox.vertices.push_back({ x_axe.min , y_axe.min });

}

void	Entity::updatePolys()
{
	for (convexPolygon& poly : m_polygons)
	{
		int size = poly.vertices.size();
		for (int i = 0; i < poly.vertices.size(); ++i)
		{
			Vector2f vertex = { (poly.vertices.at(i).m_x * m_scale + m_destRec.x) , (poly.vertices.at(i).m_y * m_scale + m_destRec.y) };
			vertex = rotatePoint(convertPointGameScreen(m_collisionBox.local.origin), vertex, m_rotation);
			poly.vertices.at(i) = vertex;
		}
	}
}