#pragma once

#include <vector>

#include "raylib.h"

#include "Coordinates.hpp"
#include "Vector2f.hpp"
#include "Entity/Entity.hpp"

class Mine : public Entity
{
	protected:
		float						m_scales[3] = { 0.12f, 0.3f, 0.66f };
		float						m_mineSpeeds[3] = { 150.f, 120.f, 60.f};
		float						m_followDelay = 0.1f;
		int							m_points[4][3] = { {200, 135, 100}, {425, 360, 325}, {600, 535, 500}, {850, 585, 750} };
		Coordinates					m_targetPos = { 0.f, 0.f };
		bool						m_hasTarget = false;
		
		enum class					m_Attribute
		{
			speed,
			points
		};

	public:
		Mine() = delete;
		Mine(const Coordinates& startPos, const Texture2D& texture, int sizeId, int typeId);
		Mine(const Mine& other);


		void						operator=(const Mine& other);
		void						locateTarget(std::vector<Coordinates>& positions);
		virtual void				update(float elapsedTime) override;
		void						updateMagPolys();

		inline int					getPoints() { return m_points[m_typeId][m_sizeId]; };

};
