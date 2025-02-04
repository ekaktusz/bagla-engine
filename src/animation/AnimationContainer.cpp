#include "animation/AnimationContainer.h"
#include "animation/Animation.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <spdlog/spdlog.h>

#define IF_EMPTY_RETURN                                                                                                                                                  \
	if (m_Animations.empty())                                                                                                                                            \
	{                                                                                                                                                                    \
		SPDLOG_WARN("AnimationComponent is empty, add an Animation to it.");                                                                                            \
		return;                                                                                                                                                          \
	}

namespace bgl
{
void AnimationContainer::addAnimation(const std::string& id, std::unique_ptr<Animation> animation)
{
	if (m_Animations.empty())
		m_CurrentAnimationID = id;
	m_Animations.try_emplace(id, std::move(animation));
}

void AnimationContainer::removeAnimation(const std::string& id)
{
	IF_EMPTY_RETURN

	if (!m_Animations.contains(id))
	{
		SPDLOG_ERROR("Can't find animation by id: " + id);
		return;
	}

	if (id == m_CurrentAnimationID)
	{
		SPDLOG_ERROR("Can't remove current animations: " + id);
		return;
	}

	m_Animations.erase(id);
}

void AnimationContainer::update(const sf::Time& dt)
{
	IF_EMPTY_RETURN
	m_Animations[m_CurrentAnimationID]->update(dt);
}

void AnimationContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	IF_EMPTY_RETURN
	target.draw(*m_Animations.at(m_CurrentAnimationID));
}

void AnimationContainer::setCurrentAnimation(const std::string& id)
{
	IF_EMPTY_RETURN
	if (m_CurrentAnimationID == id)
		return;

	if (!m_Animations.contains(id))
	{
		SPDLOG_ERROR("ID does not exist: " + id);
		return;
	}
	m_Animations[m_CurrentAnimationID]->pause();
	m_CurrentAnimationID = id;
	m_Animations[m_CurrentAnimationID]->play();
}

void AnimationContainer::setPosition(float x, float y)
{
	for (auto& [id, animation] : m_Animations)
	{
		animation->setPosition(x, y);
	}
}

void AnimationContainer::setPosition(sf::Vector2f position)
{
	for (auto& [id, animation] : m_Animations)
	{
		animation->setPosition(position);
	}
}

void AnimationContainer::setScale(float x, float y)
{
	for (auto& [id, animation] : m_Animations)
	{
		animation->setScale(x, y);
	}
}

void AnimationContainer::setScale(sf::Vector2f scale)
{
	for (auto& [id, animation] : m_Animations)
	{
		animation->setScale(scale);
	}
}

void AnimationContainer::flipHorizontally(bool flip)
{
	for (auto& [id, animation] : m_Animations)
	{
		animation->flipHorizontally(flip);
	}
}

void AnimationContainer::flipVertically(bool flip)
{
	for (auto& [id, animation] : m_Animations)
	{
		animation->flipVertically(flip);
	}
}

void AnimationContainer::pause()
{
	IF_EMPTY_RETURN
	m_Animations[m_CurrentAnimationID]->pause();
}

void AnimationContainer::play()
{
	IF_EMPTY_RETURN
	m_Animations[m_CurrentAnimationID]->play();
}
}