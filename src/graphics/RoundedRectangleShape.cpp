#include "graphics/RoundedRectangleShape.h"
#include <cmath>

namespace bgl
{
	RoundedRectangleShape::RoundedRectangleShape(sf::Vector2f size, float radius, unsigned int cornerPoints)
		: m_size(size), m_radius(radius), m_cornerPoints(cornerPoints) 
	{
		update();
	}
	
	void RoundedRectangleShape::setSize(sf::Vector2f size)
	{
		m_size = size;
		update();
	}

	sf::Vector2f RoundedRectangleShape::getSize() const
	{
		return m_size;
	}

	void RoundedRectangleShape::setCornerRadius(float radius)
	{
		m_radius = radius;
		update();
	}

	float RoundedRectangleShape::getCornerRadius() const
	{
		return m_radius;
	}

	std::size_t RoundedRectangleShape::getPointCount() const
	{
		return m_cornerPoints * 4;
	}

	sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
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

} // namespace sf