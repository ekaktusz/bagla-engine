#include "animation/Animation.h"

namespace bgl
{
	Animation::Animation(const sf::Texture& spriteSheetTexture, sf::Vector2u frameSize, 
		sf::Vector2u startFrameCoordinates, sf::Vector2u endFrameCoordinates, const sf::Time& deltaTime, bool repeating /*= true*/) : 
		m_SpriteSheet(spriteSheetTexture),
		m_FrameSize(frameSize), 
		m_StartFrameCoordinates(startFrameCoordinates), 
		m_EndFrameCoordinates(endFrameCoordinates), 
		m_DeltaTime(deltaTime), 
		m_Repeating(repeating)
	{

	}

	Animation::~Animation()
	{

	}

	void Animation::play()
	{

	}

	void Animation::pause()
	{

	}

	void Animation::setRepeating(bool repeating)
	{
		m_Repeating = repeating;
	}

	bool Animation::getRepeating() const
	{
		return m_Repeating;
	}

	void Animation::setDeltaTime(const sf::Time& deltaTime)
	{
		m_DeltaTime = deltaTime;
	}

	const sf::Time& Animation::getDeltaTime() const
	{
		return m_DeltaTime;
	}

	void Animation::update(const sf::Time& dt)
	{

	}

	void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}

	void Animation::handleEvent(const sf::Event& event)
	{

	}
}