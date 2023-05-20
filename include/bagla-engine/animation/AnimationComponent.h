#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "animation/Animation.h"

namespace sf 
{ 
	class Time; 
	class RenderTarget;
}

namespace bgl
{
	class AnimationComponent : public sf::Drawable
	{
	public:
		void addAnimation(const std::string& id, std::unique_ptr<Animation> animation);
		void removeAnimation(const std::string& id);

		void update(const sf::Time& dt);
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
		std::unordered_map<std::string, std::unique_ptr<Animation>> m_Animations;
		std::string m_CurrentAnimationID;
	};
}