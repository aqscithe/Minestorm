#pragma once

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "Entity/Mine/Mine.hpp"

class MagneticMine : public virtual Mine
{
	protected:

	public:
		MagneticMine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId);

		void	updatePolys();

};