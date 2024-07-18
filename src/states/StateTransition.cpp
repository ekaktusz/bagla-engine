#pragma once

#include "states/StateTransition.h"

namespace bgl
{
	
	StateTransition::StateTransition(Type type) : m_Type(type)
	{
		m_TransitionBackground = sf::RectangleShape({ 1270, 720 });
	}


	void StateTransition::update(const sf::Time& dt)
	{
		if (m_TransitionStarted && !isTransitionOver())
		{
			const float alpha = [&]() {
				switch (m_Type) {
				case Type::Close: return bgl::mapValue(m_TransitionClock.getElapsedTime().asSeconds(), 0.f, m_TransitionDuration.asSeconds(), 0.f, 255.f);
				case Type::Open: return 255 - bgl::mapValue(m_TransitionClock.getElapsedTime().asSeconds(), 0.f, m_TransitionDuration.asSeconds(), 0.f, 255.f);
				default: return 0.f;
				}
				}();
			m_TransitionBackground.setFillColor(sf::Color(0, 0, 0, alpha));
		}
	}

	void StateTransition::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_TransitionBackground);
	}

	void StateTransition::handleEvent(const sf::Event& event)
	{

	}

	bool StateTransition::isTransitionOver() const
	{
		return m_TransitionStarted && (m_TransitionClock.getElapsedTime() > m_TransitionDuration);
	}

	bool StateTransition::isTransitionRunning() const
	{
		return m_TransitionStarted && !isTransitionOver();
	}

	bool StateTransition::isTransitionStarted() const
	{
		return m_TransitionStarted;
	}

	void StateTransition::start()
	{
		m_TransitionStarted = true;
		m_TransitionClock.restart();

		if (m_Type == Type::Close)
		{
			m_TransitionBackground.setFillColor(sf::Color(0, 0, 0, 0));
		}
		else if (m_Type == Type::Open)
		{
			m_TransitionBackground.setFillColor(sf::Color(0, 0, 0, 255));
		}
	}

	void StateTransition::reset()
	{
		m_TransitionStarted = false;
	}
}