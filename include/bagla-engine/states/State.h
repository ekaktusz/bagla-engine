#pragma once

namespace sf
{
	class Time;
	class Event;
	class RenderWindow;
}

namespace bgl
{
	class StateManager;

	class State
	{
	public:
		State(StateManager& stateManager, sf::RenderWindow& renderWindow) : m_StateManager(stateManager), m_RenderWindow(renderWindow) {}
		virtual ~State() {}

		virtual void update(const sf::Time& dt) = 0;
		virtual void draw() const = 0;
		virtual void handleEvent(const sf::Event& event) = 0;

		virtual void onResume() {}
		virtual void onPause() {}

	protected:
		StateManager& m_StateManager;
		sf::RenderWindow& m_RenderWindow;
	};

}