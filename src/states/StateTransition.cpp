#include "states/StateTransition.h"
#include "MathExtensions.h"

namespace bgl
{

StateTransition::StateTransition(Type type) : _type(type)
{
	_transitionBackground = sf::RectangleShape({ 1270, 720 });
}

void StateTransition::update(const sf::Time& dt)
{
	if (_transitionStarted && !isTransitionOver())
	{
		const float alpha = [&]() {
			switch (_type)
			{
				case Type::Close: return bgl::mapValue(_transitionClock.getElapsedTime().asSeconds(), 0.f, _transitionDuration.asSeconds(), 0.f, 255.f);
				case Type::Open: return 255 - bgl::mapValue(_transitionClock.getElapsedTime().asSeconds(), 0.f, _transitionDuration.asSeconds(), 0.f, 255.f);
				default: return 0.f;
			}
		}();
		_transitionBackground.setFillColor(sf::Color(0, 0, 0, alpha));
	}
}

void StateTransition::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_transitionBackground);
}

void StateTransition::handleEvent(const sf::Event& event) {}

bool StateTransition::isTransitionOver() const
{
	return _transitionStarted && (_transitionClock.getElapsedTime() > _transitionDuration);
}

bool StateTransition::isTransitionRunning() const
{
	return _transitionStarted && !isTransitionOver();
}

bool StateTransition::isTransitionStarted() const
{
	return _transitionStarted;
}

void StateTransition::start()
{
	_transitionStarted = true;
	_transitionClock.restart();

	if (_type == Type::Close)
	{
		_transitionBackground.setFillColor(sf::Color(0, 0, 0, 0));
	}
	else if (_type == Type::Open)
	{
		_transitionBackground.setFillColor(sf::Color(0, 0, 0, 255));
	}
}

void StateTransition::reset()
{
	_transitionStarted = false;
}
}