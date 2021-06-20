#pragma once

#include "Fireball.hpp"

Fireball::Fireball(const Texture2D& texture, float scale, const Vector2f& dirVec, const Coordinates& pos, Rectangle rec, float rotation, int typeId) : Projectile(texture, scale, dirVec, pos, rec, rotation, typeId)
{
	// width 172 ; height 172
	// center 86, 86

	m_angularSpeed = 0.5f;

	m_shape.vertices.push_back({ -86.f, 0.f });

	m_shape.vertices.push_back({ -49.f, -23.f });
	m_shape.vertices.push_back({ -77.f, -77.f });
	m_shape.vertices.push_back({ -27.f, -49.f });

	m_shape.vertices.push_back({ 0.f, -86.f });

	m_shape.vertices.push_back({ 22.f, -49.f });
	m_shape.vertices.push_back({ 76.f, -77.f});
	m_shape.vertices.push_back({ 49.f, -27.f });

	m_shape.vertices.push_back({ 86.f, 0.f });

	m_shape.vertices.push_back({ 49.f, 22.f });
	m_shape.vertices.push_back({ 76.5f, 76.f });
	m_shape.vertices.push_back({ 22.f, 48.f });

	m_shape.vertices.push_back({ 0.f, 86.f });

	m_shape.vertices.push_back({ -27.f, 49.f });
	m_shape.vertices.push_back({ -77.f, 77.f });
	m_shape.vertices.push_back({ -49.f, 23.f });
}