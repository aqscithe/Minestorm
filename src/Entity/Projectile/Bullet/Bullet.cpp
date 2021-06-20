#pragma once

#include "Bullet.hpp"

Bullet::Bullet(const Texture2D& texture, float scale, const Vector2f& dirVec, const Coordinates& pos, Rectangle rec, float rotation, int typeId) : Projectile(texture, scale, dirVec, pos, rec, rotation, typeId)
{
	m_lifetime = 1.3f;

	m_shape.vertices.push_back({ -13.f, 0.f });
	m_shape.vertices.push_back({ 0.f, -13.f });
	m_shape.vertices.push_back({ 13.f, 0.f });
	m_shape.vertices.push_back({ 0.f, 13.f });
}

