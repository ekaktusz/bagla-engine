#include "states/StateManager.h"
#include <spdlog/spdlog.h>

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

}
