#pragma once
#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
class Time;
class Event;
}

namespace bgl
{
struct GameObject : public sf::Drawable
{
	virtual ~GameObject() {}

	virtual void update(const sf::Time& dt) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
}