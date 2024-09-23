#pragma once

#include "EventHandler.h"
#include "GameObject.h"

#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
class Time;
class Event;
}

namespace bgl
{
class Widget : public GameObject, public sf::Drawable, public EventHandler
{
public:
	virtual ~Widget() = default;
	void update(const sf::Time& dt) override = 0;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	void handleEvent(const sf::Event& event) override = 0;
};
}