#pragma once

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "Entity/Mine/Mine.hpp"

class FloatingMine : public Mine
{
	protected:
		

	public:
		FloatingMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId);

};

