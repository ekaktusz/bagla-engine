#pragma once

#include "EventHandler.h"
#include "GameObject.h"

#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
class Time;
class Event;
class RenderWindow;
}

namespace bgl
{
class StateManager;

class State : public GameObject, public EventHandler, public sf::Drawable
{
public:
	State(StateManager& stateManager, sf::RenderWindow& renderWindow) : _stateManager(stateManager), _renderWindow(renderWindow) {}

	virtual ~State() = default;

	void update(const sf::Time& dt) override = 0;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	void handleEvent(const sf::Event& event) override = 0;

	virtual void onStart() {}

	virtual void onResume() {}

	virtual void onPause() {}

protected:
	StateManager& _stateManager;
	sf::RenderWindow& _renderWindow;
};

}