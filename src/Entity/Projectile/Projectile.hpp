#pragma once

#include "raylib.h"

#include "Entity/Entity.hpp"

class Projectile : public Entity
{
	protected:
		float						m_projectileSpeeds[2] = { BULLET_SPEED, FIREBALL_SPEED };
		int							m_projectileTypes[2] = { 0, 0 };
		float						m_lifetime = 5.f;
		
	public:
		explicit Projectile(const Texture2D& texture, float scale, const Vector2f& dirVec, const Coordinates& pos, Rectangle rec, float rotation, int typeId);

		Projectile() = delete;
		Projectile(const Projectile& other);

		void						operator=(const Projectile& other);
		Coordinates					calculateStartPos(const Texture2D& texture, const Coordinates& pos, Rectangle rec, float rotation);
		void						update(float elapsedTime) override;
		bool						isBullet();
		bool						isFireball();

		static constexpr float		BULLET_SPEED = 20.f;
		static constexpr float		FIREBALL_SPEED = 10.f;
};