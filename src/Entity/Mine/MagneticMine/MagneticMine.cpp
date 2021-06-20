
#include "MagneticMine.hpp"
#include "MathToolbox/maths.hpp"
#include "MathToolbox/geo_calculs.hpp"

MagneticMine::MagneticMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId) : Mine(startPos, texture, sizeId, typeId)
{
	// width 98 ; height 102
	// center 49, 51

	// par rapport au origine

	m_shape.vertices.push_back({ 49.f, -49.f });
	m_shape.vertices.push_back({ 26.f, 0.f });
	m_shape.vertices.push_back({ 47.f, 47.f });
	m_shape.vertices.push_back({ 1.f, 26.f });
	m_shape.vertices.push_back({ -49.f, 51.f});
	m_shape.vertices.push_back({ -26.f, 2.f});
	m_shape.vertices.push_back({ -48.f, -48.f });
	m_shape.vertices.push_back({  1.f, -26.f});

}

void	MagneticMine::updatePolys()
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