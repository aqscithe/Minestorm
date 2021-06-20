#pragma once

#include <vector>
#include <array>

#include "Entity/Entity.hpp"
#include "Entity/Spawn/Spawn.hpp"
#include "Entity/Projectile/Projectile.hpp"
#include "Entity/Mine/Mine.hpp"
#include "Entity/Spaceship/Spaceship.hpp"


typedef struct metadata
{
	int typeId;
	int sizeId;

	bool	operator==(int deleteCode)
	{
		return (typeId == deleteCode && sizeId == deleteCode);
	}
} metadata;


namespace tools
{
	void	cleanVectors(std::vector<Spawn>& spawns, std::vector<Projectile>& projectiles, std::vector<Mine>& mines, std::vector<Spaceship>& ships);
}