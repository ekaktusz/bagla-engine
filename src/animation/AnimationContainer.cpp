#include "animation/AnimationContainer.h"
#include "animation/Animation.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <spdlog/spdlog.h>

#define IF_EMPTY_RETURN                                                                                                                                                  \
	if (_animations.empty())                                                                                                                                             \
	{                                                                                                                                                                    \
		SPDLOG_WARN("AnimationComponent is empty, add an Animation to it.");                                                                                            \
		return;                                                                                                                                                          \
	}

namespace bgl
{
void AnimationContainer::addAnimation(const std::string& id, std::unique_ptr<Animation> animation)
{
	if (_animations.empty())
		_currentAnimationID = id;
	_animations.try_emplace(id, std::move(animation));
}

void AnimationContainer::removeAnimation(const std::string& id)
{
	IF_EMPTY_RETURN

	if (!_animations.contains(id))
	{
		SPDLOG_ERROR("Can't find animation by id: " + id);
		return;
	}

	if (id == _currentAnimationID)
	{
		SPDLOG_ERROR("Can't remove current animations: " + id);
		return;
	}

	_animations.erase(id);
}

void AnimationContainer::update(const sf::Time& dt)
{
	IF_EMPTY_RETURN
	_animations[_currentAnimationID]->update(dt);
}

void AnimationContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	IF_EMPTY_RETURN
	target.draw(*_animations.at(_currentAnimationID));
}

void AnimationContainer::setCurrentAnimation(const std::string& id)
{
	IF_EMPTY_RETURN
	if (_currentAnimationID == id)
		return;

	if (!_animations.contains(id))
	{
		SPDLOG_ERROR("ID does not exist: " + id);
		return;
	}
	_animations[_currentAnimationID]->pause();
	_currentAnimationID = id;
	_animations[_currentAnimationID]->play();
}

void AnimationContainer::setPosition(float x, float y)
{
	for (auto& [id, animation] : _animations)
	{
		animation->setPosition(x, y);
	}
}

void AnimationContainer::setPosition(sf::Vector2f position)
{
	for (auto& [id, animation] : _animations)
	{
		animation->setPosition(position);
	}
}

void AnimationContainer::setScale(float x, float y)
{
	for (auto& [id, animation] : _animations)
	{
		animation->setScale(x, y);
	}
}

void AnimationContainer::setScale(sf::Vector2f scale)
{
	for (auto& [id, animation] : _animations)
	{
		animation->setScale(scale);
	}
}

void AnimationContainer::flipHorizontally(bool flip)
{
	for (auto& [id, animation] : _animations)
	{
		animation->flipHorizontally(flip);
	}
}

void AnimationContainer::flipVertically(bool flip)
{
	for (auto& [id, animation] : _animations)
	{
		animation->flipVertically(flip);
	}
}

void AnimationContainer::pause()
{
	IF_EMPTY_RETURN
	_animations[_currentAnimationID]->pause();
}

void AnimationContainer::play()
{
	IF_EMPTY_RETURN
	_animations[_currentAnimationID]->play();
}
}