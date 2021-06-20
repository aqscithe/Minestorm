#pragma once

#include <string>
#include <fstream>

#include "raylib.h"

#include "LevelManager.hpp"

class Game
{
    private:
        LevelManager                m_levelManager;
        Texture2D                   m_textures[11] = { 0 };
        unsigned int                m_score = 0;
        unsigned int                m_playerCount = 2;
        int                         m_screenState = 0;
        int                         m_screens[5] = {0, 1, 2, 3, 4};
        int                         m_livesP1 = 3;
        int                         m_livesP2 = 3;
        bool                        m_collisionLinesActive = false;

        enum class                  m_Screen
        {
            MAIN_MENU = 0,
            PAUSED = 1,
            IN_GAME = 2,
            GAME_OVER = 3,
            EXITING = 4
        };

        
        void                        unloadAssets();
        void                        loadAssets();
        void                        draw();
        void                        drawScreen();
        void                        gameOverScreen();
        void                        readLevels(std::string file);
        void                        inGame();
        void	                    update(float elapsedTime);
        void                        mainMenu();
        void                        pauseScreen();
        void                        drawInstructions();
        void                        drawBubble();
        void                        drawPlayerInfo(bool ingame = false);
        void                        drawScore();
        void                        setScreenState();

    public:
        Game();
        ~Game();

        void                        init();
        void                        run();
        void                        shutdown();

        static constexpr int        SCREEN_WIDTH = 640;
        static constexpr int        SCREEN_HEIGHT = 800;
        
};