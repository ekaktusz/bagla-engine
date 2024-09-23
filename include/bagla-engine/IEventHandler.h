#pragma once

namespace sf
{
class Event;
}

namespace bgl
{
class IEventHandler
{
	virtual ~IEventHandler = default;
	virtual void handleEvent(const sf::Event& event) = 0;
};
}