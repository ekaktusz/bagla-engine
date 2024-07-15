#pragma once

#include "GameObject.h"
#include "states/StateTransition.h"
namespace sf
{
	class Time;
	class Event;
	class RenderWindow;
}

namespace bgl
{
	class StateManager;

	class State : public GameObject
	{
	public:
		State(StateManager& stateManager, sf::RenderWindow& renderWindow) : m_StateManager(stateManager), m_RenderWindow(renderWindow) {}
		virtual ~State() {}

		virtual void update(const sf::Time& dt) = 0;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
		virtual void handleEvent(const sf::Event& event) = 0;

		virtual void onStart() {}
		virtual void onResume() {}
		virtual void onPause() {}

	protected:
		StateManager& m_StateManager;
		sf::RenderWindow& m_RenderWindow;

		StateTransition m_OpenTransition {StateTransition::Type::Open};
		StateTransition m_CloseTransition {StateTransition::Type::Close};
	};

}