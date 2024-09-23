#pragma once

#include "GameObject.h"
#include "MathExtensions.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace bgl
{
class StateTransition : public bgl::GameObject
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
	sf::RectangleShape m_TransitionBackground {};
	sf::Clock m_TransitionClock {};
	sf::Time m_TransitionDuration = sf::seconds(0.5f);
	Type m_Type;
	bool m_TransitionStarted = false;
};
}
