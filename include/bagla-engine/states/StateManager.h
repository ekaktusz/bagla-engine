#pragma once

#include <stack>
#include <memory>
#include <vector>

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
		void resetToFirstState();

		void applyPendingChanges();
	private:
		void handlePushState(std::unique_ptr<State> state);
		void handlePopState();
		void handleSwitchState(std::unique_ptr<State> state);
		void handleResetToFirstState();

		enum class StateManagerRequestType
		{
			Push, Pop, Switch, Reset
		};

		struct StateManagerRequest
		{
			StateManagerRequest(std::unique_ptr<State> state, StateManagerRequestType type) : requestState(std::move(state)), requestType(type) {}
			std::unique_ptr<State> requestState;
			StateManagerRequestType requestType;
		};

		std::vector<StateManagerRequest> m_RequestQueue;

		std::stack <std::unique_ptr<State>> m_States;
	};

}
