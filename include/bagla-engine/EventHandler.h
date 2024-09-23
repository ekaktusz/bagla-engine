#pragma once

namespace sf
{
class Event;
}

namespace bgl
{
struct EventHandler
{
	virtual ~EventHandler() = default;
	virtual void handleEvent(const sf::Event& event) = 0;
};
}