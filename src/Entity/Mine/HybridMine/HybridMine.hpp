#pragma once

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "Entity/Mine/Mine.hpp"
#include "Entity/Mine/MagneticMine/MagneticMine.hpp"
#include "Entity/Mine/FireballMine/FireballMine.hpp"

class HybridMine : public FireballMine, public MagneticMine
{
	protected:

	public:
		HybridMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId);

};

