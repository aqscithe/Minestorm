#pragma once

#include "raylib.h"

#include "Entity/Projectile/Projectile.hpp"

class Bullet : public Projectile
{
	private:

	public:
		Bullet(const Texture2D& texture, float scale, const Vector2f& dirVec, const Coordinates& pos, Rectangle rec, float rotation, int typeId);

};