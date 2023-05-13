#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace sf { class Time; }

namespace bgl
{ 
	class Animation;

	class AnimationComponent
	{
	public:
		void addAnimation(const std::string& id, std::unique_ptr<Animation> animation);
		void removeAnimation(const std::string& id);

		void update(const sf::Time& dt);

		void setCurrentAnimation(const std::string& id);

		void pause();
		void play();

	private:
		std::unordered_map<std::string, std::unique_ptr<Animation>> m_Animations;
		std::string m_CurrentAnimationID;
	};
}