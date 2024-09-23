#pragma once

#include "IGameObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace sf
{
class Time;
}

namespace bgl
{
<<<<<<< Updated upstream
class Animation : public GameObject
{
public:
	Animation(const sf::Texture& spriteSheetTexture, sf::Vector2i frameSize, sf::Vector2i startFrameCoordinates, sf::Vector2i endFrameCoordinates,
		const sf::Time& deltaTime, bool repeating = true);
=======
	class Animation : public IGameObject, public sf::Drawable
	{
	public:
		Animation(const sf::Texture& spriteSheetTexture, sf::Vector2i frameSize, sf::Vector2i startFrameCoordinates, sf::Vector2i endFrameCoordinates, const sf::Time& deltaTime, bool repeating = true);
>>>>>>> Stashed changes

	void play();
	void pause();

	void setRepeating(bool repeating);
	bool getRepeating() const;

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);

	sf::Vector2f getPosition() const;

	sf::Vector2f getSize() const;

	void setDeltaTime(const sf::Time& deltaTime);
	const sf::Time& getDeltaTime() const;

	void setScale(sf::Vector2f scale);
	void setScale(float x, float y);
	sf::Vector2f getScale() const;

<<<<<<< Updated upstream
	void update(const sf::Time& dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event) override;
=======
		void update(const sf::Time& dt) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
>>>>>>> Stashed changes

	void flipHorizontally(bool flip);
	void flipVertically(bool flip);

private:
	void jumpToNextFrame();

private:
	sf::Sprite m_Sprite;
	sf::Texture m_SpriteSheet;

	sf::Vector2i m_FrameSize;
	sf::Vector2i m_StartFrameCoordinates;
	sf::Vector2i m_EndFrameCoordinates;
	sf::Vector2i m_CurrentFrameCoordinates;

	sf::IntRect m_CurrentFrame;

	sf::Time m_DeltaTime;
	sf::Clock m_Timer;

	bool m_Playing = false;
	bool m_Repeating = true;

	bool m_FlippedHorizontally = false;
	bool m_FlippedVertically = false;
};
}