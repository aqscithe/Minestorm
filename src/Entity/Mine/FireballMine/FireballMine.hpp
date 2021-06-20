#pragma once

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "Entity/Mine/Mine.hpp"

class FireballMine : public virtual Mine
{
	protected:

	public:
		FireballMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId);

};