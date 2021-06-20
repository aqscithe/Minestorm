#pragma once

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "Entity/Entity.hpp"

class Spawn : public Entity
{
	protected:

	

	public:
		explicit Spawn(const Coordinates& pos, const Texture2D* texture);
		Spawn() = delete;
		Spawn(const Spawn& other);


		void	operator=(const Spawn& other);
		void	update(float elapsedTime) override;

};