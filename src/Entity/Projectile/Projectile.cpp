#pragma once

#include <iostream>

#include "Projectile.hpp"
#include "MathToolbox/geo_calculs.hpp"
#include "MathToolbox/maths.hpp"

Projectile::Projectile(const Texture2D& texture, float scale, const Vector2f& dirVec, const Coordinates& pos, Rectangle rec, float rotation, int typeId)
{
	m_typeId = typeId;
	m_projectileTypes[m_typeId] = 1;
	m_position = this->calculateStartPos(texture, pos, rec, rotation);
	m_speed = { dirVec.m_x * m_projectileSpeeds[m_typeId], dirVec.m_y * m_projectileSpeeds[m_typeId] };

	m_position = pos;
	m_texture = texture;
	m_scale = scale;
	m_sourceRec.width = texture.width;
	m_sourceRec.height = texture.height;
	m_destRec.width = m_texture.width * m_scale;
	m_destRec.height = m_texture.height * m_scale;
	m_destRec.x = m_position.getX();
	m_destRec.y = m_position.getY();
	m_origin = { m_texture.width * m_scale / 2, m_texture.height * m_scale / 2 };
	
}

Projectile::Projectile(const Projectile& other)
{
	*this = other;
}

void Projectile::operator=(const Projectile& other)
{
	m_lifetime = other.m_lifetime;

	int speedsCount = sizeof(m_projectileSpeeds) / sizeof(m_projectileSpeeds[0]);
	int typesCount = sizeof(m_projectileTypes) / sizeof(m_projectileTypes[0]);

	for (int i = 0; i < typesCount; ++i)
	{
		this->m_projectileSpeeds[i] = other.m_projectileSpeeds[i];
	}
	for (int i = 0; i < speedsCount; ++i)
	{
		this->m_projectileTypes[i] = other.m_projectileTypes[i];
	}

	Entity::equalize(other);
}

Coordinates		Projectile::calculateStartPos(const Texture2D& texture, const Coordinates& shipPos, Rectangle rec, float rotation)
{
	return { shipPos.getX() + (rec.height + 0.5f * texture.height) / 2 * cosf(m_rotation * maths::M_PI / 180.f),
		shipPos.getY() + (rec.height + 0.5f * texture.height) / 2 * sinf(m_rotation * maths::M_PI / 180.f) };
}

void	Projectile::update(float elapsedTime)
{
	m_lifetime -= elapsedTime;
	if (m_lifetime <= 0.f && m_lifetime > -99.f)
		m_markedForDeletion = true;

	auto distance = m_speed * elapsedTime;
	m_position += distance;
	m_rotation = angleClamp(m_rotation + m_angularSpeed);

	m_destRec.x = this->getPosition().getX();
	m_destRec.y = this->getPosition().getY();

	if (m_collisionsActive)
		Entity::updateAABB();
}

bool	Projectile::isBullet()
{
	return m_projectileTypes[m_typeId];
}

bool	Projectile::isFireball()
{
	return m_projectileTypes[m_typeId];
}
