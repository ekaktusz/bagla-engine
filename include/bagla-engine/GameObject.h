#pragma once
#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
	class Time;
	class Event;
}

namespace bgl
{
	class GameObject : public sf::Drawable
	{
		virtual void update(const sf::Time& dt) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void handleEvent(const sf::Event& event) = 0;
	};
}