#pragma once


#include "Entity/Projectile/Projectile.hpp"

class Fireball : public Projectile
{
	private:

	public:
		Fireball(const Texture2D& texture, float scale, const Vector2f& dirVec, const Coordinates& pos, Rectangle rec, float rotation, int typeId);

};