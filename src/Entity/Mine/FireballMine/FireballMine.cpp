

#include "FireballMine.hpp"

FireballMine::FireballMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId) : Mine(startPos, texture, sizeId, typeId)
{
	
	// width 104 ; height 105
	// center 51, 52.5

	m_shape.vertices.push_back({ 51.f, -52.5f });
	m_shape.vertices.push_back({ 39.f, 0.f });
	m_shape.vertices.push_back({ 51.5f, 52.5f });
	m_shape.vertices.push_back({ 0.f, -39.5f });
	m_shape.vertices.push_back({ -51.f, 52.5f });
	m_shape.vertices.push_back({ -39.f, 0.f });
	m_shape.vertices.push_back({ -51.f, -52.f });
}