#include "graphics/RoundedRectangleShape.h"
#include <cmath>

namespace bgl
{
RoundedRectangleShape::RoundedRectangleShape(sf::Vector2f size, float radius, unsigned int cornerPoints) : _size(size), _radius(radius), _cornerPoints(cornerPoints)
{
	update();
}

void RoundedRectangleShape::setSize(sf::Vector2f size)
{
	_size = size;
	update();
}

sf::Vector2f RoundedRectangleShape::getSize() const
{
	return _size;
}

void RoundedRectangleShape::setCornerRadius(float radius)
{
	_radius = radius;
	update();
}

float RoundedRectangleShape::getCornerRadius() const
{
	return _radius;
}

std::size_t RoundedRectangleShape::getPointCount() const
{
	return _cornerPoints * 4;
}

sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
{
	if (index >= getPointCount())
		return sf::Vector2f(0, 0);

	float deltaAngle = 90.0f / (_cornerPoints - 1);
	sf::Vector2f center;
	unsigned int centerIndex = index / _cornerPoints;
	unsigned int localIndex = index % _cornerPoints;

	switch (centerIndex)
	{
		case 0:
			center.x = _size.x - _radius;
			center.y = _radius;
			break;
		case 1:
			center.x = _radius;
			center.y = _radius;
			break;
		case 2:
			center.x = _radius;
			center.y = _size.y - _radius;
			break;
		case 3:
			center.x = _size.x - _radius;
			center.y = _size.y - _radius;
			break;
	}

	float angle = deltaAngle * localIndex + 90.0f * centerIndex;
	float radian = angle * 3.14159265358979323846 / 180.0f;

	return sf::Vector2f(_radius * std::cos(radian) + center.x, -_radius * std::sin(radian) + center.y);
}

} // namespace sf