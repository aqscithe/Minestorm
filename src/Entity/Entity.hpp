#pragma once

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "MathToolbox/primitives.hpp"

class Entity
{
	protected:
		int								m_typeId = -1;
		int								m_sizeId = -1;
		float							m_angularSpeed = 0.f;
		Vector2f						m_direction = { 0.f, 0.f };
		Vector2f						m_speed = { 0.f, 0.f };
		Vector2f						m_origin = { 0.f, 0.f };
		float							m_rotation = 0.f;
		float							m_scale = 1.f;
		Coordinates						m_position;
		Texture2D						m_texture = { 0, 0, 0, 0, 0 };
		Rectangle						m_sourceRec = { 0, 0, 0, 0 };
		Rectangle						m_destRec = { 0, 0, 0, 0 };
		Color							m_bodyColor = WHITE;
		Color							m_collisionLines = RED;
		convexPolygon					m_collisionBox;
		convexPolygon					m_shape;
		bool							m_collisionsActive = true;
		std::vector<convexPolygon>		m_polygons;
		

	public:
		bool							m_colliding = false;
		bool							m_markedForDeletion = false;

		Entity();
		virtual ~Entity();

		Entity(const Entity& other) = delete; 
		void operator=(const Entity& other) = delete; 

		bool							operator==(int deleteCode);
		void							equalize(const Entity& other);
		virtual void					updateCollision(bool collisionHandled = false);
		void							updateAABB();
		void							updateTemp(bool collided);
		void							draw(bool collisionLinesActive);
		virtual void					update(float elapsedTime);
		virtual void					updatePolys();
		
		inline int						getType() const { return m_typeId; };
		inline int						getSize() const { return m_sizeId; };
		inline convexPolygon			getAABB() const { return m_collisionBox; };
		inline Vector2f					getSpeedVector() const { return m_speed; };
		inline Vector2f					getDirectionVector() const { return m_direction; };
		inline Rectangle				getDestRec() const { return m_destRec; };
		inline float					getRotation() const { return m_rotation; };
		inline Coordinates				getPosition() const { return m_position; };
};