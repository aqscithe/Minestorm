#pragma once

#include "raylib.h"

#include "../../Coordinates.hpp"
#include "../../Vector2f.hpp"
#include "../Entity.hpp"

class Spaceship : public Entity
{
	private:
		int								m_playerNum = 0;
		int								m_lives = 3;
		bool							m_accelerating = false;
		bool							m_turningLeft = false;
		bool							m_turningRight = false;
		bool							m_firing = false;
		float							m_explosionTimer = 1.2f;
		float							m_respawnTimer = 2.5f;
		
		int								m_controls[2][6] = { {KEY_R, KEY_D, KEY_G, KEY_F, KEY_T, KEY_E}, { KEY_I, KEY_J, KEY_L, KEY_K, KEY_U, KEY_O} };
		enum class Controls
		{
			forward,
			left,
			right,
			fire,
			teleport1,
			teleport2
		};

		

	public:
		bool							m_respawning = false;
		bool							m_exploding = false;

		Spaceship() = delete;
		Spaceship(int playerNum, const Texture2D& texture, float scale);
		Spaceship(const Spaceship& other);


		void							operator=(const Spaceship& other);
		void							updateCollision(bool collisionHandled = false) override;
		void							resetShip();
		void							setState();
		void							setBodyColor();
		void							update(float elapsedTime) override;
		void							updatePolys();
		void							handleRespawn(float elapsedTime);
		void							teleport();
		float							driftCorrection();

		inline int						getLives() const { return m_lives; };
		inline int						getPlayer() const { return m_playerNum; };
		inline bool						fired() const { return m_firing; };

		static constexpr float			THRUST = 600000.f;  
		static constexpr float			MASS = 200;
		static constexpr float			ANG_SPEED = 250.f;
		static constexpr float			DRIFT_COEFF = 0.f;
		static constexpr float			FRICTION_COEFF = 4.f;

};