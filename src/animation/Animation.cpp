#include "animation/Animation.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <spdlog/spdlog.h>

namespace bgl
{
Animation::Animation(const sf::Texture& spriteSheetTexture, sf::Vector2i frameSize, sf::Vector2i startFrameCoordinates, sf::Vector2i endFrameCoordinates,
	const sf::Time& deltaTime, bool repeating /*= true*/) :
	_spriteSheet(spriteSheetTexture),
	_frameSize(frameSize),
	_startFrameCoordinates(startFrameCoordinates),
	_endFrameCoordinates(endFrameCoordinates),
	_currentFrameCoordinates(startFrameCoordinates),
	_deltaTime(deltaTime),
	_repeating(repeating)
{
	_sprite.setTexture(_spriteSheet);
	_currentFrame = { frameSize.x * _currentFrameCoordinates.x, frameSize.y * _currentFrameCoordinates.y, frameSize.x, frameSize.y };
	_sprite.setTextureRect(_currentFrame);

	play();
}

void Animation::play()
{
	if (!_playing)
	{
		_timer.restart();
		_playing = true;
	}
}

void Animation::pause()
{
	_playing = false;
}

void Animation::setRepeating(bool repeating)
{
	_repeating = repeating;
}

bool Animation::getRepeating() const
{
	return _repeating;
}

void Animation::setPosition(float x, float y)
{
	_sprite.setPosition(x, y);
}

sf::Vector2f Animation::getPosition() const
{
	return _sprite.getPosition();
}

sf::Vector2f Animation::getSize() const
{
	return { _sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height };
}

void Animation::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Animation::setDeltaTime(const sf::Time& deltaTime)
{
	_deltaTime = deltaTime;
}

const sf::Time& Animation::getDeltaTime() const
{
	return _deltaTime;
}

void Animation::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Animation::setScale(float x, float y)
{
	_sprite.setScale(x, y);
}

sf::Vector2f Animation::getScale() const
{
	return _sprite.getScale();
}

void Animation::update(const sf::Time& dt)
{
	if (!_playing)
		return;
	if (_timer.getElapsedTime() >= _deltaTime)
	{
		jumpToNextFrame();
		_timer.restart();
	}
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void Animation::flipHorizontally(bool flip)
{
	if (_flippedHorizontally != flip)
	{
		_flippedHorizontally = flip;
		jumpToNextFrame(); // cause the flip is not applied on the current frame. could be nicer
	}
}

void Animation::flipVertically(bool flip)
{
	_flippedVertically = flip;
}

void Animation::jumpToNextFrame()
{
	const sf::Vector2f gridSize(_spriteSheet.getSize().x / _frameSize.x, _spriteSheet.getSize().y / _frameSize.y);

	if (_endFrameCoordinates.y != _startFrameCoordinates.y)
	{
		// TODO
	}
	else
	{
		if (_currentFrameCoordinates.x < _endFrameCoordinates.x)
		{
			_currentFrameCoordinates.x++;
		}
		else
		{
			_currentFrameCoordinates.x = 0;
		}
	}

	_currentFrame.left = _frameSize.x * _currentFrameCoordinates.x;
	_currentFrame.top = _frameSize.y * _currentFrameCoordinates.y;

	if (_flippedHorizontally)
	{
		_currentFrame.width = -std::abs(_currentFrame.width);
		_currentFrame.left += std::abs(_currentFrame.width);
	}
	else
	{
		_currentFrame.width = std::abs(_currentFrame.width);
	}

	_sprite.setTextureRect(_currentFrame);
}
}