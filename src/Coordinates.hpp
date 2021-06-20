#pragma once

#include "Vector2f.hpp"

class Coordinates
{
	private:
		float						m_x = m_spaceLength / 2.f;
		float						m_y = m_spaceHeight / 2.f;

		static int					m_spaceLength;
		static int					m_spaceHeight;
		static Vector2f				m_worldOrigin;
		static int					m_bottomOffset;
		static int					m_topOffset;
		static int					m_leftOffset;
		static int					m_rightOffset;
		static int					m_maxScreenX;
		static int					m_minScreenX;
		static int					m_maxScreenY;
		static int					m_minScreenY;
		

		void recalculate();

	public:
		Coordinates();
		Coordinates(float px, float py);
		~Coordinates() = default;

		void						operator+=(Vector2f const& vector);

		float						calculateDistance(Coordinates const& other) const;

		static void					initializeSpace(int length, int height);

		inline float				getX() const { return m_x; };
		inline float				getY() const { return m_y; };

		static inline int			getGameLength() { return m_spaceLength - m_rightOffset - m_leftOffset; };
		static inline int			getGameHeight() { return m_spaceHeight - m_bottomOffset - m_topOffset; };
		static inline Vector2f		worldOrigin() { return m_worldOrigin; };
		static inline int			getSpaceLength() { return m_spaceLength; };
		static inline int			getSpaceHeight() { return m_spaceHeight; };
		static inline int			getBottomOffset() { return m_bottomOffset; };
		static inline int			getTopOffset() { return m_topOffset; };
		static inline int			getLeftOffset() { return m_leftOffset; };
		static inline int			getRightOffset() { return m_rightOffset; };

		

};