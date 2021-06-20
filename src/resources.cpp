//#include <algorithm>
#include <iostream>

#include "resources.hpp"

void	tools::cleanVectors(std::vector<Spawn>& spawns, std::vector<Projectile>& projectiles, std::vector<Mine>& mines, std::vector<Spaceship>& ships)
{
	mines.erase(std::remove(mines.begin(), mines.end(), -99), mines.end());
	spawns.erase(std::remove(spawns.begin(), spawns.end(), -99), spawns.end());
	projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), -99), projectiles.end());
	ships.erase(std::remove(ships.begin(), ships.end(), -99), ships.end());

}

/*
void	tools::cleanVector(std::vector<Spawn>& spawns)
{
	
	//return spawns;

	/*
	spawns.erase(std::remove_if(spawns.begin(), spawns.end(), [](Spawn* pi) {
		if (pi->m_markedForDeletion) {
			delete pi;
			return true;
		}
		return false; }
	), spawns.end());
	return false;
	*/
	//std::stable_partition(vec.begin(), vec.end(), [](int* pi) { return *pi % 2 != 0; });

	/*
	auto firstToRemove = std::stable_partition(spawns.begin(), spawns.end(), [](Spawn spawn) { return !spawn.m_markedForDeletion; });
	std::for_each(firstToRemove, spawns.end(), [](Spawn spawn) { delete spawn; });
	spawns.erase(firstToRemove, spawns.end());
	*/
	
