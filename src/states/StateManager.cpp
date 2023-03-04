#include "states/StateManager.h"
#include <spdlog/spdlog.h>

#define IF_EMPTY_RETURN if (m_States.empty()) { spdlog::error("State stack is empty!"); return; }


namespace bgl
{
	void StateManager::pushState(std::unique_ptr<State> state)
	{
		if (!m_States.empty())
		{
			m_States.top()->onPause();
		}
		m_States.push(std::move(state));
	}


	void StateManager::popState()
	{
		IF_EMPTY_RETURN
		
		m_States.pop();

		if (!m_States.empty())
		{
			m_States.top()->onResume();
		}
	}

	void StateManager::switchState(std::unique_ptr<State> state)
	{
		IF_EMPTY_RETURN

		popState();
		pushState(std::move(state));
	}


	void StateManager::update(const sf::Time& dt)
	{
		IF_EMPTY_RETURN

		m_States.top()->update(dt);
	}

	void StateManager::draw() const
	{
		IF_EMPTY_RETURN

		m_States.top()->draw();
	}

	void StateManager::handleEvent(const sf::Event& event)
	{
		IF_EMPTY_RETURN

		m_States.top()->handleEvent(event);
	}
}
