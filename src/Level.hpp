#pragma once

#include <string>
#include <vector>
#include <array>
#include <random>

#include "Coordinates.hpp"
#include "Entity/Spaceship/Spaceship.hpp"
#include "Entity/Spawn/Spawn.hpp"
#include "Entity/Mine/Mine.hpp"
#include "Entity/Mine/FloatingMine/FloatingMine.hpp"
#include "Entity/Mine/FireballMine/FireballMine.hpp"
#include "Entity/Mine/MagneticMine/MagneticMine.hpp"
#include "Entity/Mine/HybridMine/HybridMine.hpp"
#include "Entity/Projectile/Projectile.hpp"
#include "Entity/Projectile/Fireball/Fireball.hpp"
#include "Entity/Projectile/Bullet/Bullet.hpp"
#include "resources.hpp"

class Level
{
    private:

        bool                                m_levelStarted = false;
        float                               m_startTimer = 1.f;
        float                               m_spawnTimer = 5.f;  
        int                                 m_setsSpawned = 0;
        int                                 m_spawnSets = 0;
        int                                 m_mineTypes[4] = { 0, 0, 0, 0 };
        std::string                         m_levelCode = "";
        std::vector<Mine>                   m_mines;
        std::vector<Projectile>             m_projectiles;
        std::vector<Spawn>                  m_spawnPoints;
        std::vector<Spaceship>              m_ships;
        std::vector<metadata>               m_spawnQueue;

        void                                initLevel(const Texture2D* textures);
        void                                setSpawns(int spawnCount, const Texture2D* textures);
        void                                manageInitialSpawns(float elapsedTime, const Texture2D* textures);
        void                                spawnInitialMine(const Texture2D* textures);
        void                                spawnMine(int mineType, int sizeId, const Texture2D* textures);
        void                                setStates();
        void                                updatePositions(float elapsedTime, const Texture2D* textures);
        void                                testCollisions();
        void                                spawnFromQueue(const Texture2D* textures);
        std::vector<Coordinates>            locateShips();

    public:
        explicit Level(std::string str);

        Level&                              operator=(const Level& other);
        void                                createPlayers(int playerCount, const Texture2D& shipTexture);
        void                                display(bool collisionLinesActive, const Texture2D* textures, unsigned int& score, int& livesP1, int& livesP2);
        void                                update(float elapsedTime, const Texture2D* textures, bool& levelComplete);
        void                                cleanUp();

        inline std::vector<Spaceship>&      getPlayers() { return m_ships; };
};