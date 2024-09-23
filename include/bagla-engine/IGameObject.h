#pragma once

namespace sf
{
class Time;
}

namespace bgl
{

struct IGameObject
{
	virtual ~IGameObject() = default;
	virtual void update(const sf::Time& dt) = 0;
};

}