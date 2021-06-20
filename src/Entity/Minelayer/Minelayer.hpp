#pragma once

#include "raylib.h"

#include "../../Coordinates.hpp"
#include "../../Vector2f.hpp"
#include "Entity/Entity.hpp"

class Minelayer : public Entity
{
	private:
	
	public:
		explicit Minelayer(const Coordinates& startPos, const Texture2D& texture, float scale);

		Minelayer() = delete;
		Minelayer(const Minelayer& other) = delete;


		void						operator=(const Minelayer& other) = delete;
		void						update(float elapsedTime) override;

		static constexpr float		MINELAYER_SPEED = 45.f;
};