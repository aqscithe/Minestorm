#include <iostream>

#include "LevelManager.hpp"

LevelManager::LevelManager()
{}

LevelManager::~LevelManager()
{
}


void    LevelManager::setTextures(const Texture2D* textures)
{
	m_textures = textures;
}

void    LevelManager::setPlayers(int playerCount)
{
	if (m_levelIndex == 0)
		m_levels.at(0).createPlayers(playerCount, m_textures[2]);
	else // copy players from old level into new level
	{
		for (int i = 0; i < playerCount; ++i)
		{
			m_levels.at(m_levelIndex).getPlayers().push_back(m_levels.at(m_levelIndex - 1).getPlayers().at(i));
		}
	}
}


void	LevelManager::addLevel(std::string str)
{
	m_levelCodes.push_back(str);
	m_levels.push_back(Level(str));
}

void	LevelManager::drawLevel(bool collisionLinesActive, unsigned int& score, int& livesP1, int& livesP2)
{
	m_levels.at(m_levelIndex).display(collisionLinesActive, m_textures, score, livesP1, livesP2);
}

void    LevelManager::clearLevels()
{
	for (int i = 0; i < m_levels.size(); ++i)
	{
		m_levels.at(i) = Level(m_levelCodes.at(i));
	}
	m_levelIndex = 0;
}

void	LevelManager::update(float elapsedTime)
{
	m_levels.at(m_levelIndex).update(elapsedTime, m_textures, m_levelComplete);
	if (m_levelComplete)
	{
		if ((m_levelIndex + 1) == m_levels.size())
		{
			std::cout << "le jeu est terminé" << std::endl;
		}
		else if (m_nextLevelDelay < 0.f)
		{
			++m_levelIndex;
			m_nextLevelDelay = 5.f;
			m_levelComplete = false;
			LevelManager::setPlayers(m_levels.at(m_levelIndex - 1).getPlayers().size());
		}
		else
		{
			m_nextLevelDelay -= elapsedTime;
		}
	}
	

}