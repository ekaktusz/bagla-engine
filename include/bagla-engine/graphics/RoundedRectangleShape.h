#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <cmath>

namespace bgl
{
	class RoundedRectangleShape : public sf::Shape
	{
	public:
		RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0), float radius = 0, unsigned int cornerPoints = 30)
			: m_size(size), m_radius(radius), m_cornerPoints(cornerPoints)
		{
			update();
		}

		void setSize(const sf::Vector2f& size)
		{
			m_size = size;
			update();
		}

		const sf::Vector2f& getSize() const
		{
			return m_size;
		}

		void setCornerRadius(float radius)
		{
			m_radius = radius;
			update();
		}

		float getCornerRadius() const
		{
			return m_radius;
		}

		void setCornerPointCount(unsigned int count)
		{
			m_cornerPoints = count;
			update();
		}

		virtual std::size_t getPointCount() const
		{
			return m_cornerPoints * 4;
		}

		virtual sf::Vector2f getPoint(std::size_t index) const
		{
			if (index >= getPointCount())
				return sf::Vector2f(0, 0);

			float deltaAngle = 90.0f / (m_cornerPoints - 1);
			sf::Vector2f center;
			unsigned int centerIndex = index / m_cornerPoints;
			unsigned int localIndex = index % m_cornerPoints;

			switch (centerIndex)
			{
			case 0: center.x = m_size.x - m_radius; center.y = m_radius; break;
			case 1: center.x = m_radius; center.y = m_radius; break;
			case 2: center.x = m_radius; center.y = m_size.y - m_radius; break;
			case 3: center.x = m_size.x - m_radius; center.y = m_size.y - m_radius; break;
			}

			float angle = deltaAngle * localIndex + 90.0f * centerIndex;
			float radian = angle * 3.14159265358979323846 / 180.0f;

			return sf::Vector2f(m_radius * std::cos(radian) + center.x,
				-m_radius * std::sin(radian) + center.y);

		}

	private:
		sf::Vector2f m_size;
		float m_radius;
		unsigned int m_cornerPoints;
	};
}
