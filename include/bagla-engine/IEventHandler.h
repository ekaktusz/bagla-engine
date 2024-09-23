#pragma once


namespace sf
{
class Event;
}

namespace bgl
{
struct IEventHandler
{
	virtual ~IEventHandler() = default;
	virtual void handleEvent(const sf::Event& event) = 0;
};
}