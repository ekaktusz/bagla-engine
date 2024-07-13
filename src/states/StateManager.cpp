#include "states/StateManager.h"

#include <memory>
#include <spdlog/spdlog.h>
#include <states/State.h>
#include <type_traits>

#define IF_EMPTY_RETURN if (m_States.empty()) { spdlog::error("State stack is empty!"); return; }

namespace bgl
{
	void StateManager::handlePushState(std::unique_ptr<State> state)
	{
		if (!m_States.empty())
		{
			m_States.top()->onPause();
		}
		m_States.push(std::move(state));
		m_States.top()->onStart();
	}

	void StateManager::handlePopState()
	{
		IF_EMPTY_RETURN

		m_States.pop();

		if (!m_States.empty())
		{
			m_States.top()->onResume();
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

		while (m_States.size() > 1)
		{
			m_States.pop();
		}

		m_States.top()->onResume();
	}

	void StateManager::applyPendingChanges()
	{
		for (StateManagerRequest& pendingRequest : m_RequestQueue)
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

		m_RequestQueue.clear();
	}

	void StateManager::update(const sf::Time& dt)
	{
		if (!m_States.empty())
		{
			m_States.top()->update(dt);
		}
		applyPendingChanges();
	}

	void StateManager::draw() const
	{
		if (!m_States.empty())
		{
			m_States.top()->draw();
		}
	}

	void StateManager::handleEvent(const sf::Event& event)
	{
		if (!m_States.empty())
		{
			m_States.top()->handleEvent(event);
		}
		applyPendingChanges();
	}

	void StateManager::pushState(std::unique_ptr<State> state)
	{
		m_RequestQueue.push_back({ std::move(state), StateManagerRequestType::Push });
	}

	void StateManager::popState()
	{
		m_RequestQueue.push_back({ nullptr, StateManagerRequestType::Pop });
	}

	void StateManager::switchState(std::unique_ptr<State> state)
	{
		m_RequestQueue.push_back({ std::move(state), StateManagerRequestType::Switch });
	}

	void StateManager::resetToFirstState()
	{
		m_RequestQueue.push_back({ nullptr, StateManagerRequestType::Reset });
	}

}
