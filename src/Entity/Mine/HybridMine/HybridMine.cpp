
#include "HybridMine.hpp"

HybridMine::HybridMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId) : MagneticMine(startPos, texture, sizeId, typeId), FireballMine(startPos, texture, sizeId, typeId), Mine(startPos, texture, sizeId, typeId)
{
	// width 146 ; height 152
	// center 73, 76

	m_shape.vertices.push_back({ -73.f, 45.f });
	m_shape.vertices.push_back({ -45.f, 31.f});
	m_shape.vertices.push_back({ -45.f, -75.f});
	m_shape.vertices.push_back({ -31.f, -46.f });
	m_shape.vertices.push_back({ 73.f, -45.f });
	m_shape.vertices.push_back({ 40.f, -27.f});
	m_shape.vertices.push_back({ 40.f, 75.f });
	m_shape.vertices.push_back({ 28.f, 45.f});

}