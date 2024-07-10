#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace bgl
{
	class RoundedRectangleShape : public sf::Shape
	{
	public:
		RoundedRectangleShape(sf::Vector2f size = { 0, 0}, float radius = 0, unsigned int cornerPoints = 30);

		void setSize(sf::Vector2f size);
		sf::Vector2f getSize() const;

		void setCornerRadius(float radius);
		float getCornerRadius() const;

		virtual std::size_t getPointCount() const override;
		virtual sf::Vector2f getPoint(std::size_t index) const override;

	private:
		sf::Vector2f m_size;
		float m_radius;
		unsigned int m_cornerPoints;
	};
}
