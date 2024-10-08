#include "animation/Animation.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <spdlog/spdlog.h>

namespace bgl
{
Animation::Animation(const sf::Texture& spriteSheetTexture, sf::Vector2i frameSize, sf::Vector2i startFrameCoordinates, sf::Vector2i endFrameCoordinates,
	const sf::Time& deltaTime, bool repeating /*= true*/) :
	m_SpriteSheet(spriteSheetTexture),
	m_FrameSize(frameSize),
	m_StartFrameCoordinates(startFrameCoordinates),
	m_EndFrameCoordinates(endFrameCoordinates),
	m_CurrentFrameCoordinates(startFrameCoordinates),
	m_DeltaTime(deltaTime),
	m_Repeating(repeating)
{
	m_Sprite.setTexture(m_SpriteSheet);
	m_CurrentFrame = { frameSize.x * m_CurrentFrameCoordinates.x, frameSize.y * m_CurrentFrameCoordinates.y, frameSize.x, frameSize.y };
	m_Sprite.setTextureRect(m_CurrentFrame);

	play();
}

void Animation::play()
{
	if (!m_Playing)
	{
		m_Timer.restart();
		m_Playing = true;
	}
}

void Animation::pause()
{
	m_Playing = false;
}

void Animation::setRepeating(bool repeating)
{
	m_Repeating = repeating;
}

bool Animation::getRepeating() const
{
	return m_Repeating;
}

void Animation::setPosition(float x, float y)
{
	m_Sprite.setPosition(x, y);
}

sf::Vector2f Animation::getPosition() const
{
	return m_Sprite.getPosition();
}

sf::Vector2f Animation::getSize() const
{
	return { m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height };
}

void Animation::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Animation::setDeltaTime(const sf::Time& deltaTime)
{
	m_DeltaTime = deltaTime;
}

const sf::Time& Animation::getDeltaTime() const
{
	return m_DeltaTime;
}

void Animation::setScale(sf::Vector2f scale)
{
	m_Sprite.setScale(scale);
}

void Animation::setScale(float x, float y)
{
	m_Sprite.setScale(x, y);
}

sf::Vector2f Animation::getScale() const
{
	return m_Sprite.getScale();
}

void Animation::update(const sf::Time& dt)
{
	if (!m_Playing)
		return;
	if (m_Timer.getElapsedTime() >= m_DeltaTime)
	{
		jumpToNextFrame();
		m_Timer.restart();
	}
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}


void Animation::flipHorizontally(bool flip)
{
	if (m_FlippedHorizontally != flip)
	{
		m_FlippedHorizontally = flip;
		jumpToNextFrame(); // cause the flip is not applied on the current frame. could be nicer
	}
}

void Animation::flipVertically(bool flip)
{
	m_FlippedVertically = flip;
}

void Animation::jumpToNextFrame()
{
	const sf::Vector2f gridSize(m_SpriteSheet.getSize().x / m_FrameSize.x, m_SpriteSheet.getSize().y / m_FrameSize.y);

	if (m_EndFrameCoordinates.y != m_StartFrameCoordinates.y)
	{
		// TODO
	}
	else
	{
		if (m_CurrentFrameCoordinates.x < m_EndFrameCoordinates.x)
		{
			m_CurrentFrameCoordinates.x++;
		}
		else
		{
			m_CurrentFrameCoordinates.x = 0;
		}
	}

	m_CurrentFrame.left = m_FrameSize.x * m_CurrentFrameCoordinates.x;
	m_CurrentFrame.top = m_FrameSize.y * m_CurrentFrameCoordinates.y;

	if (m_FlippedHorizontally)
	{
		m_CurrentFrame.width = -std::abs(m_CurrentFrame.width);
		m_CurrentFrame.left += std::abs(m_CurrentFrame.width);
	}
	else
	{
		m_CurrentFrame.width = std::abs(m_CurrentFrame.width);
	}

	m_Sprite.setTextureRect(m_CurrentFrame);
}
}