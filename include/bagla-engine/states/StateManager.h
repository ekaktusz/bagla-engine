#pragma once

#include <stack>
#include <memory>

#include "State.h"

namespace bgl
{
	class StateManager
	{
	public:
		void update(const sf::Time& dt);
		void draw() const;
		void handleEvent(const sf::Event& event);

		void pushState(std::unique_ptr<State> state);
		void popState();
		void switchState(std::unique_ptr<State> state);
	private:
		std::stack <std::unique_ptr<State>> m_States;
	};

}
