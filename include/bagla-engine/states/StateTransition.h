#pragma once

#include "EventHandler.h"
#include "GameObject.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace bgl
{
class StateTransition : public GameObject, public sf::Drawable, public EventHandler
{
public:
	enum class Type
	{
		Open,
		Close
	};

public:
	StateTransition(Type type);

	void update(const sf::Time& dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event) override;

	void start();
	void reset();

	bool isTransitionOver() const;
	bool isTransitionRunning() const;
	bool isTransitionStarted() const;

private:
	sf::RectangleShape _transitionBackground {};
	sf::Clock _transitionClock {};
	sf::Time _transitionDuration = sf::seconds(0.5f);
	Type _type;
	bool _transitionStarted = false;
};
}
