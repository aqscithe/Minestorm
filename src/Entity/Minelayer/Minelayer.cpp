#pragma once

#include "Minelayer.hpp"

#include "MathToolbox/geo_calculs.hpp"

Minelayer::Minelayer(const Coordinates& startPos, const Texture2D& texture, float scale)
{
	m_position = startPos;
	m_texture = texture;
	m_sourceRec.width = texture.width;
	m_sourceRec.height = texture.height;
	m_destRec.width = m_texture.width * m_scale;
	m_destRec.height = m_texture.height * m_scale;
	m_origin = { m_texture.width * m_scale / 2, m_texture.height * m_scale / 2 };


	m_angularSpeed = 0.2f;
	// width 254 ; height 78
	// center 127, 39

	// par rapport au origine

	m_shape.vertices.push_back({ -127.f, 39.f });
	m_shape.vertices.push_back({ -107.f, -11.f });
	m_shape.vertices.push_back({ -35.f, -11.f });
	m_shape.vertices.push_back({ 0.f, -39.f });
	m_shape.vertices.push_back({ 35.f, -11.f});
	m_shape.vertices.push_back({ 106.f, -11.f });
	m_shape.vertices.push_back({ 127.f, 39.f });
	m_shape.vertices.push_back({ 106.f, 24.f });
	m_shape.vertices.push_back({ -106.f, 24.f });
}

void	Minelayer::update(float elapsedTime)
{
	// faire des mis à jours qui sont uniquement pour le mine

	// Entity update
	Entity::update(elapsedTime);
}