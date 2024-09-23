#pragma once

namespace sf
{
class Time;
}

namespace bgl
{
struct GameObject
{
	virtual ~GameObject() = default;
	virtual void update(const sf::Time& dt) = 0;
};
}