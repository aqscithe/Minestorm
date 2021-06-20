#pragma once

#include <random>
#include <iostream>
#include "math.h"

#include "Spaceship.hpp"
#include "MathToolbox/maths.hpp"
#include "MathToolbox/geo_calculs.hpp"

Spaceship::Spaceship(int playerNum, const Texture2D& texture, float scale)
{
	if (playerNum > 2 || playerNum < 1)
	{
		std::cerr << "Invalid Player Number Set" << std::endl;
		exit(1);
	}
	m_playerNum = playerNum;

	m_texture = texture;
	m_scale = scale;
	m_sourceRec.width = texture.width;
	m_sourceRec.height = texture.height;
	m_destRec.width = m_texture.width * m_scale;
	m_destRec.height = m_texture.height * m_scale;
	m_origin = { m_texture.width * m_scale / 2, m_texture.height * m_scale / 2 };

	if (m_playerNum == 1)
	{
		m_position = { Coordinates::getSpaceLength() / 3.5f, Coordinates::getSpaceHeight() / 2.f };
		m_bodyColor = BLUE;
	}
	else if (m_playerNum == 2)
	{
		m_position = { Coordinates::getSpaceLength() / 1.5f, Coordinates::getSpaceHeight() / 2.f };
		m_bodyColor = GREEN;
	}
		

	// width 84 ; height 140
	// center 42, 70

	// par rapport au origine

	m_shape.vertices.push_back({ 0.f, -70.f });
	m_shape.vertices.push_back({ 18.f, -30.f });
	m_shape.vertices.push_back({ -19.f, -30.f });

	m_shape.vertices.push_back({ 13.f, 14.f });
	m_shape.vertices.push_back({ -14.f, 14.f });

	m_shape.vertices.push_back({ -26.f, 2.f });
	m_shape.vertices.push_back({ -42.f, 50.f });
	m_shape.vertices.push_back({ -17.f, 57.f });

	m_shape.vertices.push_back({ 24.f, 2.f });
	m_shape.vertices.push_back({ 42.f, 50.f });
	m_shape.vertices.push_back({ 17.f, 57.f });

	

	m_shape.vertices.push_back({ 31.f, 14.f });
	m_shape.vertices.push_back({ 31.f, 59.f});
	m_shape.vertices.push_back({ 31.f, 70.f });
	m_shape.vertices.push_back({ 17.f, 70.f });
	
	m_shape.vertices.push_back({ -17.f, 70.f });
	m_shape.vertices.push_back({ -32.f, 70.f });
	m_shape.vertices.push_back({ -32.f, 57.f });
	m_shape.vertices.push_back({ -32.f, 14.f });
	
	
	
}

Spaceship::Spaceship(const Spaceship& other)
{
	*this = other;
}

void Spaceship::operator=(const Spaceship& other)
{
	m_playerNum = other.m_playerNum;
	m_lives = other.m_lives;
	m_accelerating = other.m_accelerating;
	m_turningLeft = other.m_turningLeft;
	m_turningRight = other.m_turningRight;
	m_firing = other.m_firing;
	m_explosionTimer = other.m_explosionTimer;
	m_respawnTimer = other.m_respawnTimer;
	this->m_respawning = other.m_respawning;
	this->m_exploding = other.m_exploding;

	int playerCount = sizeof(m_controls) / sizeof(m_controls[0]);
	int controlCount = sizeof(m_controls[0]) / sizeof(m_controls[0][0]);
	for (int i = 0; i < playerCount; ++i)
		for (int j = 0; j < controlCount; ++j)
			m_controls[i][j] = other.m_controls[i][j];

	Entity::equalize(other);
}

void	Spaceship::updateCollision(bool collisionHandled)
{
	if (m_colliding && collisionHandled && m_lives > 0 && !m_exploding && !m_respawning)
	{
		std::cout << "Player " << m_playerNum << " lost a life" << std::endl;
		--m_lives;
		m_exploding = true;
		Spaceship::resetShip();
		Entity::updateCollision(false);
	}
	else if (m_lives <= 0)
		Entity::updateCollision(true);
	else
		Entity::updateCollision(false);
}

void Spaceship::resetShip()
{
	m_position = { Coordinates::getSpaceLength() / 2.f, Coordinates::getSpaceHeight() / 2.f };
	m_speed = { 0.f, 0.f };
	m_rotation = 0.f;
}

void	Spaceship::setState()
{
	if (!m_exploding)
	{
		m_accelerating = IsKeyDown(m_controls[m_playerNum - 1][(int)Controls::forward]);
		m_turningLeft = IsKeyDown(m_controls[m_playerNum - 1][(int)Controls::left]);
		m_turningRight = IsKeyDown(m_controls[m_playerNum - 1][(int)Controls::right]);
		m_firing = IsKeyPressed(m_controls[m_playerNum - 1][(int)Controls::fire]);
	}
	
	Spaceship::setBodyColor();
}

void Spaceship::setBodyColor()
{
	if (m_exploding)
		m_bodyColor = { 255, 255, 255, 0 };
	else if (m_respawning)
		m_bodyColor = { 255, 255, 255, 50 };
	else if (m_playerNum == 1)
		m_bodyColor = BLUE;
	else if (m_playerNum == 2)
		m_bodyColor = GREEN;
}

void	Spaceship::update(float elapsedTime)
{
	Spaceship::handleRespawn(elapsedTime);

	if (m_collisionsActive)
		Spaceship::updatePolys();

	if (IsKeyPressed(m_controls[m_playerNum - 1][(int)Controls::teleport1]) || IsKeyPressed(m_controls[m_playerNum - 1][(int)Controls::teleport2]))
	{
		this->teleport();
	}
	if (m_accelerating)
	{
		m_speed += Vector2f::fromAngle(THRUST / MASS * elapsedTime, (m_rotation - 90.f) * this->driftCorrection());
	}
	m_speed -= m_speed * FRICTION_COEFF * elapsedTime;
	Entity::update(elapsedTime);

	if (m_turningLeft)
	{
		m_angularSpeed = -ANG_SPEED * elapsedTime;
	}
	else if (m_turningRight)
	{
		m_angularSpeed = ANG_SPEED * elapsedTime;
	}
	else
		m_angularSpeed = 0;

	
	
}

void	Spaceship::updatePolys()
{
	convexPolygon nosecone;
	nosecone.vertices.push_back(m_shape.vertices.at(0));
	nosecone.vertices.push_back(m_shape.vertices.at(1));
	nosecone.vertices.push_back(m_shape.vertices.at(2));
	nosecone.local.angle = m_rotation;
	nosecone.local.origin = maths::getPolyOrigin(nosecone.vertices.at(0), nosecone.vertices.at(1), nosecone.vertices.at(2));
	m_polygons.push_back(nosecone);

	convexPolygon body;
	body.vertices.push_back(m_shape.vertices.at(1));
	body.vertices.push_back(m_shape.vertices.at(3));
	body.vertices.push_back(m_shape.vertices.at(4));
	body.vertices.push_back(m_shape.vertices.at(2));
	body.local.angle = m_rotation;
	body.local.origin = maths::getPolyOrigin(body.vertices.at(0), body.vertices.at(1), body.vertices.at(2), body.vertices.at(3));
	m_polygons.push_back(body);

	convexPolygon leftthrust;
	leftthrust.vertices.push_back(m_shape.vertices.at(5));
	leftthrust.vertices.push_back(m_shape.vertices.at(6));
	leftthrust.vertices.push_back(m_shape.vertices.at(7));
	leftthrust.local.angle = m_rotation;
	leftthrust.local.origin = maths::getPolyOrigin(leftthrust.vertices.at(0), leftthrust.vertices.at(1), leftthrust.vertices.at(2));
	m_polygons.push_back(leftthrust);

	convexPolygon rightthrust;
	rightthrust.vertices.push_back(m_shape.vertices.at(8));
	rightthrust.vertices.push_back(m_shape.vertices.at(9));
	rightthrust.vertices.push_back(m_shape.vertices.at(10));
	rightthrust.local.angle = m_rotation;
	rightthrust.local.origin = maths::getPolyOrigin(rightthrust.vertices.at(0), rightthrust.vertices.at(1), rightthrust.vertices.at(2));
	m_polygons.push_back(rightthrust);
}

void Spaceship::handleRespawn(float elapsedTime)
{
	if (m_respawning && m_respawnTimer > 0.f)
		m_respawnTimer -= elapsedTime;
	else if (m_respawning && m_respawnTimer <= 0.f)
	{
		m_respawning = false;
		m_respawnTimer = 2.5f;
	}
	else if (m_exploding && m_explosionTimer > 0.f)
		m_explosionTimer -= elapsedTime;
	else if (m_exploding && m_explosionTimer <= 0.f)
	{
		m_exploding = false;
		m_explosionTimer = 1.2f;
		m_respawning = true;
	}
}

float	Spaceship::driftCorrection()
{
	return (1.f - DRIFT_COEFF);// * maths::signf(v2::dotProduct(m_speed, { 1.0f, 0.f })) * (v2::getAngle(m_speed, m_direction) * 180.f / maths::M_PI) - 90.f;
}

void	Spaceship::teleport()
{
	std::random_device generator;
	auto randomPosX = std::uniform_int_distribution<int>{ Coordinates::getLeftOffset() , Coordinates::getSpaceLength() - Coordinates::getRightOffset() };
	auto randomPosY = std::uniform_int_distribution<int>{ Coordinates::getTopOffset() , Coordinates::getSpaceHeight() - Coordinates::getBottomOffset() };
	this->m_position = { (float)randomPosX(generator), (float)randomPosY(generator) };
}