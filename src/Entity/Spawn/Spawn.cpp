#include "Spawn.hpp"

Spawn::Spawn(const Coordinates& pos, const Texture2D* texture)
{
	m_texture = *texture;
	m_position = pos;
	m_scale = 0.2f;
	m_sourceRec.width = m_texture.width;
	m_sourceRec.height = m_texture.height;
	m_destRec.x = pos.getX();
	m_destRec.y = pos.getY();
	m_destRec.width = m_texture.width * m_scale;
	m_destRec.height = m_texture.height * m_scale;
	m_origin = { m_texture.width * m_scale / 2, m_texture.height * m_scale / 2 };
	m_collisionsActive = false;
}

Spawn::Spawn(const Spawn& other)
{
	*this = other;
}

void Spawn::operator=(const Spawn& other)
{
	Entity::equalize(other);
}

void	Spawn::update(float elapsedTime)
{
	
}