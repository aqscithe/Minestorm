#include <iostream>
#include <string>

#include "Level.hpp"
#include "MathToolbox/geo_calculs.hpp"



Level::Level(std::string str)
{
	m_levelCode = str;
}

Level& Level::operator=(const Level& other)
{

	int size = sizeof(m_mineTypes) / sizeof(m_mineTypes[0]);
	for (int i = 0; i < size; ++i)
		m_mineTypes[i] = other.m_mineTypes[i];

	m_levelStarted = other.m_levelStarted;
	m_levelCode = other.m_levelCode;
	m_mines = other.m_mines;
	m_spawnSets = other.m_spawnSets;
	m_setsSpawned = other.m_setsSpawned;
	m_mines = other.m_mines;
	m_ships = other.m_ships;
	m_projectiles = other.m_projectiles;
	m_spawnPoints = other.m_spawnPoints;
	m_startTimer = other.m_startTimer;
	m_spawnTimer = other.m_spawnTimer;

	return *this;
}

void	Level::initLevel(const Texture2D* textures)
{
	m_spawnSets = std::stoi(m_levelCode);
	Level::setSpawns(m_spawnSets * 7, &textures[3]);

	int types = 0;
	for (int i = 0; i < m_levelCode.size(); ++i)
	{
		if (i == 0)
			continue;
		else
		{
			switch (m_levelCode[i])
			{
				case 'F':
					if (types < m_spawnSets)
					{
						m_mineTypes[0] = 1;
						++types;
					}
					break;
				case 'B':
					if (types < m_spawnSets)
					{
						m_mineTypes[1] = 1;
						++types;
					}
					break;
				case 'M':
					if (types < m_spawnSets)
					{
						m_mineTypes[2] = 1;
						++types;
					}
					break;
				case 'H':
					if (types < m_spawnSets)
					{
						m_mineTypes[3] = 1;
						++types;
					}
					break;
				default:
					std::cerr << "Invalid mine type. Check 'levels.txt'" << std::endl;
					exit(1);
					break;
			}
		}
	}
}

void	Level::setSpawns(int spawnCount, const Texture2D* spawnTexture)
{
	std::random_device generator;
	for (int i = 0; i < spawnCount; ++i)
	{
		auto randomPosX = std::uniform_int_distribution<int>{ Coordinates::getLeftOffset() , Coordinates::getSpaceLength() - Coordinates::getRightOffset() };
		auto randomPosY = std::uniform_int_distribution<int>{ Coordinates::getTopOffset() , Coordinates::getSpaceHeight() - Coordinates::getBottomOffset() };
		m_spawnPoints.push_back(Spawn({ (float)randomPosX(generator), (float)randomPosY(generator) }, spawnTexture));
	}
}

void    Level::createPlayers(int playerCount, const Texture2D& shipTexture)
{
	for (int i = 0; i < playerCount; ++i)
		m_ships.push_back(Spaceship(i + 1, shipTexture, 0.21f));
}

void	Level::manageInitialSpawns(float elapsedTime, const Texture2D* textures)
{
	
	if (m_spawnTimer <= 0.f && m_setsSpawned == 0)
	{
		Level::spawnInitialMine(textures);
	}
	else if (m_spawnTimer <= 0.f && m_setsSpawned > 0)
	{
		Level::spawnInitialMine(textures);
	}
	else
		m_spawnTimer -= elapsedTime;
}

void	Level::spawnInitialMine(const Texture2D* textures)
{
	std::random_device generator;
	int size = sizeof(m_mineTypes) / sizeof(m_mineTypes[0]);
	auto randomMineType = std::uniform_int_distribution<int>{ 0, size - 1 }(generator);
	for (int i = 0; i < size; ++i)
	{
		if (m_mineTypes[randomMineType] == 1)
		{
			Level::spawnMine(randomMineType, 2, textures);
			++m_setsSpawned;
			m_spawnTimer = 5.f;
			break;
		}
		else if (randomMineType == size - 1)
			randomMineType = 0;
		else
			++randomMineType;
	}
	m_levelStarted = true;
}

void	Level::spawnMine(int mineType, int sizeId, const Texture2D* textures)
{
	
	int spawnPos = -1;
	if (m_spawnPoints.size() == 0)
		spawnPos = 0;
	else
	{
		for (int i = m_spawnPoints.size() - 1; i >= 0; --i)
		{

			if (m_spawnPoints.at(i).m_markedForDeletion)
				continue;
			spawnPos = i;
		}
		if (spawnPos == -1)
		{
			std::cout << "Error: Spawn point not available for mine. Exiting..." << std::endl;
			std::cout << "Mine type: " << mineType << "\tSizeId: " << sizeId << "\t# of Spawns: " << m_spawnPoints.size() << std::endl;
			exit(1);
		}
	}
	
	
	switch (mineType)
	{
	case 0:
		m_mines.push_back(FloatingMine(m_spawnPoints.at(spawnPos).getPosition(), textures[4], sizeId, mineType));
		m_spawnPoints.at(spawnPos).m_markedForDeletion = true;
		break;
	case 1:
		m_mines.push_back(FireballMine(m_spawnPoints.at(spawnPos).getPosition(), textures[5], sizeId, mineType));
		m_spawnPoints.at(spawnPos).m_markedForDeletion = true;
		break;
	case 2:
		m_mines.push_back(MagneticMine(m_spawnPoints.at(spawnPos).getPosition(), textures[6], sizeId, mineType));
		m_spawnPoints.at(spawnPos).m_markedForDeletion = true;
		break;
	case 3:
		m_mines.push_back(HybridMine(m_spawnPoints.at(spawnPos).getPosition(), textures[7], sizeId, mineType));
		m_spawnPoints.at(spawnPos).m_markedForDeletion = true;
		break;
	default:
		break;
	}
}



void    Level::update(float elapsedTime, const Texture2D* textures, bool& levelComplete)
{
	std::vector<Coordinates> shipPos;

	if (m_setsSpawned < m_spawnSets)
	{
		Level::manageInitialSpawns(elapsedTime, textures);
	}

	if (m_startTimer <= 0.f)
	{
		Level::setStates();
	}
	else
		m_startTimer -= elapsedTime;

	Level::updatePositions(elapsedTime, textures);
	Level::testCollisions();
	Level::spawnFromQueue(textures);
	shipPos = Level::locateShips();

	for (Mine& mine : m_mines)
	{
		if (mine.getType() == 2 || mine.getType() == 3)
			mine.locateTarget(shipPos);
	}
	
	if (m_mines.size() == 0 && m_levelStarted)
	{
		levelComplete = true;
	}
		
		
	
}

void	Level::setStates()
{
	for (Spaceship& element : m_ships)
		if (!element.m_markedForDeletion)
			element.setState();
}

void	Level::updatePositions(float elapsedTime, const Texture2D* textures)
{
	for (Spawn& spawn : m_spawnPoints)
		if (!spawn.m_markedForDeletion)
			spawn.update(elapsedTime);

	for (Mine& mine : m_mines)
		if (!mine.m_markedForDeletion)
			mine.update(elapsedTime);
			
	for (Projectile& projectile : m_projectiles)
		if (!projectile.m_markedForDeletion)
			projectile.update(elapsedTime);
	for (Spaceship& ship : m_ships)
	{
		if (!ship.m_markedForDeletion)
		{
			if (ship.fired())
			{
				m_projectiles.push_back(Bullet(textures[9], 0.2f, ship.getDirectionVector(), ship.getPosition(), ship.getDestRec(), ship.getRotation(), 0));
			}
			ship.update(elapsedTime);
		}
	}		
}

void	Level::testCollisions()
{
	// ship - mine collisions
	for (int i = 0; i < m_ships.size(); ++i)
	{
		if (!m_ships.at(i).m_markedForDeletion)
		{
			for (Mine& mine : m_mines)
			{
				bool collided = collision::convexPolyToConvexPoly(m_ships.at(i).getAABB(), mine.getAABB());

				m_ships.at(i).updateTemp(collided);
				mine.updateTemp(collided);
				if (i == m_ships.size() - 1 )
					mine.updateCollision();
			}
			m_ships.at(i).updateCollision(true);
		}
	}

	
	// mine - bullet collisions
	int i = 0;
	for (Mine& mine : m_mines)
	{
		for (Projectile& projectile : m_projectiles)
		{
			if (projectile.isBullet())
			{
				bool collided = collision::convexPolyToConvexPoly(mine.getAABB(), projectile.getAABB());

				mine.updateTemp(collided);
				projectile.updateTemp(collided);
				if (i == m_mines.size() - 1)
					projectile.updateCollision(true);
			}
		}
		mine.updateCollision(true);
		++i;
	}
	
}

std::vector<Coordinates> Level::locateShips()
{
	std::vector<Coordinates> positions;
	for (Spaceship& ship : m_ships)
	{
		if (!ship.m_markedForDeletion && !ship.m_exploding && !ship.m_respawning)
			positions.push_back(ship.getPosition());
	}
	return positions;
}

void	Level::spawnFromQueue(const Texture2D* textures)
{
	for (auto& data : m_spawnQueue)
	{
		Level::spawnMine(data.typeId, data.sizeId, textures);
		data = { -99, -99 };
	}
	m_spawnQueue.erase(std::remove(m_spawnQueue.begin(), m_spawnQueue.end(), -99), m_spawnQueue.end());
}

void	Level::display(bool collisionLinesActive, const Texture2D* textures, unsigned int& score, int& livesP1, int& livesP2)
{
	if (!m_spawnSets)
		Level::initLevel(textures);

	for (Mine& mine : m_mines)
	{
		if (!mine.m_markedForDeletion)
			mine.draw(collisionLinesActive);
		else if (mine.m_markedForDeletion)
		{
			score += mine.getPoints();
			if (mine.getSize() > 0)
			{
				for (int i = 0; i < 2; ++i)
				{
					std::cout << "spawning new mines" << std::endl;
					m_spawnQueue.push_back({ mine.getType(), mine.getSize() - 1 });
				}
			}
			if (mine.getType() == 1 || mine.getType() == 3)
			{
				std::vector<Coordinates> positions = Level::locateShips();
				m_projectiles.push_back(Fireball(textures[10], 0.05f, v2::getDirShortestDistance(positions, mine.getPosition()), 
					mine.getPosition(), mine.getDestRec(), mine.getRotation(), 1));
			}
			
		}
	}
		
	for (Projectile& projectile : m_projectiles)
		if (!projectile.m_markedForDeletion)
			projectile.draw(collisionLinesActive);
	for (Spawn& spawn : m_spawnPoints)
		if (!spawn.m_markedForDeletion)
			spawn.draw(collisionLinesActive);
	for (Spaceship& ship : m_ships)
	{
		if (!ship.m_markedForDeletion)
		{
			ship.draw(collisionLinesActive);
		}
		if (ship.getPlayer() == 1)
			livesP1 = ship.getLives();
		else if (ship.getPlayer() == 2)
			livesP2 = ship.getLives();
	}
			



	Level::cleanUp();
}

void	Level::cleanUp()
{
	tools::cleanVectors(m_spawnPoints, m_projectiles, m_mines, m_ships);
}





