#pragma once

#include "animation/Animation.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace sf
{
class Time;
class RenderTarget;
}

namespace bgl
{
class AnimationContainer : public GameObject, public sf::Drawable
{
public:
	AnimationContainer() = default;

	void addAnimation(const std::string& id, std::unique_ptr<Animation> animation);
	void removeAnimation(const std::string& id);

	void update(const sf::Time& dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setCurrentAnimation(const std::string& id);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);

	void setScale(float x, float y);
	void setScale(sf::Vector2f scale);

	void flipHorizontally(bool flip);
	void flipVertically(bool flip);

	void pause();
	void play();

private:
	std::unordered_map<std::string, std::unique_ptr<Animation>> _animations;
	std::string _currentAnimationID;
};
}