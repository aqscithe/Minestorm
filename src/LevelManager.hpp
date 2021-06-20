#pragma once

#include <string>
#include <vector>

#include "Level.hpp"

class LevelManager
{
    private:
        bool                        m_levelComplete = false;
        float                       m_nextLevelDelay = 5.f;
        int                         m_levelIndex = 0;
        const Texture2D*            m_textures = nullptr;
        Level*                      m_currentLevel = nullptr;
        Level*                      m_prevLevel = nullptr;
        std::vector<std::string>    m_levelCodes;
        std::vector<Level>          m_levels;

    public:
        LevelManager();
        ~LevelManager();

        void                        setPlayers(int playerCount);
        void                        setTextures(const Texture2D* textures);
        void                        addLevel(std::string str);
        void                        drawLevel(bool collisionLinesActive, unsigned int& score, int& livesP1, int& livesP2);
        void                        clearLevels();
        void                        update(float elapsedTime);
};