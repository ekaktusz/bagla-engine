#pragma once

#include "GameObject.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

namespace bgl
{
	class Animation : public GameObject
	{
	public:
		Animation(const sf::Texture& spriteSheetTexture, sf::Vector2u frameSize, sf::Vector2u startFrameCoordinates, sf::Vector2u endFrameCoordinates, const sf::Time& deltaTime, bool repeating = true);
		~Animation();

		void play();
		void pause();
		
		void setRepeating(bool repeating);
		bool getRepeating() const;

		void setDeltaTime(const sf::Time& deltaTime);
		const sf::Time& getDeltaTime() const;

		void update(const sf::Time& dt) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void handleEvent(const sf::Event& event) override;

	private:
		void nextFrame();

	private:
		sf::Sprite m_Sprite;
		sf::Texture m_SpriteSheet;
		sf::Vector2u m_FrameSize;
		sf::Vector2u m_StartFrameCoordinates;
		sf::Vector2u m_EndFrameCoordinates;
		sf::Time m_DeltaTime;
		sf::Clock m_Timer;
		sf::IntRect m_CurrentFrame;
		bool m_Playing;
		bool m_Repeating;
	};
}