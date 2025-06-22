#pragma once

#include "EventHandler.h"
#include "GameObject.h"
#include "State.h"
#include "StateTransition.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <stack>
#include <vector>

namespace bgl
{
class StateManager : public GameObject, public EventHandler
{
public:
	StateManager(sf::RenderWindow& renderWindow) : _renderWindow(renderWindow) {}

	void update(const sf::Time& dt) override;
	void draw() const;
	void handleEvent(const sf::Event& event) override;

	void applyPendingChangesWithTransition();

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
		Push,
		Pop,
		Switch,
		Reset
	};

	struct StateManagerRequest
	{
		StateManagerRequest(std::unique_ptr<State> state, StateManagerRequestType type) : requestState(std::move(state)), requestType(type) {}

		std::unique_ptr<State> requestState;
		StateManagerRequestType requestType;
	};

	std::vector<StateManagerRequest> _requestQueue;

	std::stack<std::unique_ptr<State>> _states;
	sf::RenderWindow& _renderWindow;

	StateTransition _openTransition { StateTransition::Type::Open };
	StateTransition _closeTransition { StateTransition::Type::Close };
};

}
