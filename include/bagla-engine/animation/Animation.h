#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

namespace bgl
{
	class Animation
	{
	public:
		Animation(const sf::Texture& texture, sf::Vector2u frameSize, sf::Vector2u startFrameCoordinates, sf::Vector2u endFrameCoordinates, bool repeating = true);
		~Animation();

		void play();
		void pause();
		
		void setRepeating(bool repeating);
		bool getRepeating() const;

	private:
		sf::Texture m_SpriteSheet;
		sf::Sprite m_Sprite;
		sf::Clock m_Timer;
		float m_TimePeriod;
		sf::IntRect m_CurrentFrame;
		bool m_Paused;
		bool repeating;
	};
}