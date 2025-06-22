#include "states/StateManager.h"

#include <memory>
#include <spdlog/spdlog.h>
#include <states/State.h>
#include <type_traits>

#define IF_EMPTY_RETURN                                                                                                                                                  \
	if (_states.empty())                                                                                                                                                 \
	{                                                                                                                                                                    \
		SPDLOG_ERROR("State stack is empty!");                                                                                                                           \
		return;                                                                                                                                                          \
	}

namespace bgl
{
void StateManager::handlePushState(std::unique_ptr<State> state)
{
	if (!_states.empty())
	{
		_states.top()->onPause();
	}
	_states.push(std::move(state));
	_states.top()->onStart();
	_openTransition.start();
}

void StateManager::handlePopState()
{
	IF_EMPTY_RETURN

	_states.pop();

	if (!_states.empty())
	{
		_states.top()->onResume();
		_openTransition.start();
	}
}

void StateManager::handleSwitchState(std::unique_ptr<State> state)
{
	IF_EMPTY_RETURN

	popState();
	pushState(std::move(state));
}

void StateManager::handleResetToFirstState()
{
	IF_EMPTY_RETURN

	while (_states.size() > 1)
	{
		_states.pop();
	}

	_states.top()->onResume();
	_openTransition.start();
}

void StateManager::applyPendingChanges()
{
	for (StateManagerRequest& pendingRequest : _requestQueue)
	{
		if (pendingRequest.requestType == StateManagerRequestType::Pop)
		{
			handlePopState();
		}
		else if (pendingRequest.requestType == StateManagerRequestType::Push)
		{
			handlePushState(std::move(pendingRequest.requestState));
		}
		else if (pendingRequest.requestType == StateManagerRequestType::Switch)
		{
			handleSwitchState(std::move(pendingRequest.requestState));
		}
		else if (pendingRequest.requestType == StateManagerRequestType::Reset)
		{
			handleResetToFirstState();
		}
	}

	_requestQueue.clear();
}

void StateManager::update(const sf::Time& dt)
{
	if (!_states.empty())
	{
		_states.top()->update(dt);
		_openTransition.update(dt);
		_closeTransition.update(dt);
	}
	applyPendingChangesWithTransition();
}

void StateManager::draw() const
{
	if (!_states.empty())
	{
		_renderWindow.draw(*_states.top());
		_renderWindow.draw(_openTransition);
		if (_closeTransition.isTransitionStarted())
			_renderWindow.draw(_closeTransition);
		_renderWindow.display();
	}
}

void StateManager::handleEvent(const sf::Event& event)
{
	if (!_states.empty())
	{
		_states.top()->handleEvent(event);
		_openTransition.handleEvent(event);
	}
	applyPendingChangesWithTransition();
}

void StateManager::applyPendingChangesWithTransition()
{
	if (_closeTransition.isTransitionOver())
	{
		SPDLOG_INFO("apply pending changes");
		applyPendingChanges();
		_closeTransition.reset();
	}

	if (!_requestQueue.empty() && !_closeTransition.isTransitionStarted())
	{
		SPDLOG_INFO("transition started");
		_closeTransition.start();
	}
}

void StateManager::pushState(std::unique_ptr<State> state)
{
	_requestQueue.push_back({ std::move(state), StateManagerRequestType::Push });
}

void StateManager::popState()
{
	_requestQueue.push_back({ nullptr, StateManagerRequestType::Pop });
}

void StateManager::switchState(std::unique_ptr<State> state)
{
	_requestQueue.push_back({ std::move(state), StateManagerRequestType::Switch });
}

void StateManager::resetToFirstState()
{
	_requestQueue.push_back({ nullptr, StateManagerRequestType::Reset });
}
}
