#pragma once

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "Entity/Entity.hpp"

class Spaceship : public Entity
{
	private:
		bool					m_accelerating = false;
		bool					m_turningLeft = false;
		bool					m_turningRight = false;


	public:
		Spaceship();
		Spaceship(const Texture2D& texture, float scale);

		void					setState();
		void					update(float elapsedTime) override;
		void					draw();
		void					teleport();
		float					driftCorrection();

		static constexpr float	THRUST = 100000.f;  // force
		static constexpr float	MASS = 200;
		//static constexpr float	ACCELERATION = 600.f; // l'ajoute d'un thrust fait que l'on n'a pas besoin d'une acceleration
		static constexpr float	ANG_SPEED = 250.f;
		static constexpr float	DRIFT_COEFF = 0.f;
		static constexpr float	FRICTION_COEFF = 2.f;

};