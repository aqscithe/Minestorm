#pragma once

#include <random>

#include "FloatingMine.hpp"

FloatingMine::FloatingMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId) : Mine(startPos, texture, sizeId, typeId)
{
	
	std::random_device generator;
	float dirX = std::uniform_int_distribution<int>{ -1, 1 }(generator) * 1.f;
	float dirY = std::uniform_int_distribution<int>{ -1, 1 }(generator) * 1.f;

	m_speed = { dirX * m_mineSpeeds[sizeId], dirY * m_mineSpeeds[sizeId] };
	
	// width 115 ; height 107
	// center 57.5, 53.5

	m_shape.vertices.push_back({ 0.f, -53.5f });
	m_shape.vertices.push_back({ 17.5f, 4.5f });
	m_shape.vertices.push_back({ 57.5, 53.5f });
	m_shape.vertices.push_back({ 0.f, 39.5f });
	m_shape.vertices.push_back({ -57.5f, 53.5f });
	m_shape.vertices.push_back({ -18.5f, 4.5f });
}