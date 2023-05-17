#include "animation/AnimationComponent.h"
#include "animation/Animation.h"
#include <spdlog/spdlog.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace bgl
{
	void AnimationComponent::addAnimation(const std::string& id, std::unique_ptr<Animation> animation)
	{
		if (m_Animations.empty()) m_CurrentAnimationID = id;
		m_Animations.try_emplace(id, std::move(animation));
	}

	void AnimationComponent::update(const sf::Time& dt)
	{
		m_Animations[m_CurrentAnimationID]->update(dt);
	}

	void AnimationComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		auto currentAnimationIter = m_Animations.find(m_CurrentAnimationID);
		target.draw(*currentAnimationIter->second);
	}

	void AnimationComponent::setCurrentAnimation(const std::string& id)
	{
		if (m_CurrentAnimationID == id) return;

		auto found = m_Animations.find(id);
		if (found == m_Animations.end())
		{
			spdlog::error("Can't find animation by id: " + id);
		}
		m_Animations[m_CurrentAnimationID]->pause();
		m_CurrentAnimationID = id;
		m_Animations[m_CurrentAnimationID]->play();
	}

	void AnimationComponent::setPosition(float x, float y)
	{
		
	}

	void AnimationComponent::setPosition(sf::Vector2f position)
	{

	}

	void AnimationComponent::pause()
	{
		m_Animations[m_CurrentAnimationID]->pause();
	}

	void AnimationComponent::play()
	{
		m_Animations[m_CurrentAnimationID]->play();
	}
}