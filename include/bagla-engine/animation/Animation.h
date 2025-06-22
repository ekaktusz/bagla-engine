#pragma once

#include "GameObject.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace sf
{
class Time;
}

namespace bgl
{
class Animation : public GameObject, public sf::Drawable
{
public:
	Animation(const sf::Texture& spriteSheetTexture, sf::Vector2i frameSize, sf::Vector2i startFrameCoordinates, sf::Vector2i endFrameCoordinates,
		const sf::Time& deltaTime, bool repeating = true);

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

	void update(const sf::Time& dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void flipHorizontally(bool flip);
	void flipVertically(bool flip);

private:
	void jumpToNextFrame();

private:
	sf::Sprite _sprite;
	sf::Texture _spriteSheet;

	sf::Vector2i _frameSize;
	sf::Vector2i _startFrameCoordinates;
	sf::Vector2i _endFrameCoordinates;
	sf::Vector2i _currentFrameCoordinates;

	sf::IntRect _currentFrame;

	sf::Time _deltaTime;
	sf::Clock _timer;

	bool _playing = false;
	bool _repeating = true;

	bool _flippedHorizontally = false;
	bool _flippedVertically = false;
};
}