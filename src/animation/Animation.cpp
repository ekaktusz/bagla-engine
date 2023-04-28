#include "animation/Animation.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace bgl
{
	Animation::Animation(const sf::Texture& spriteSheetTexture, sf::Vector2i frameSize, 
		sf::Vector2i startFrameCoordinates, sf::Vector2i endFrameCoordinates, const sf::Time& deltaTime, bool repeating /*= true*/) : 
		m_SpriteSheet(spriteSheetTexture),
		m_FrameSize(frameSize), 
		m_StartFrameCoordinates(startFrameCoordinates), 
		m_EndFrameCoordinates(endFrameCoordinates), 
		m_DeltaTime(deltaTime), 
		m_Repeating(repeating)
	{
		m_Sprite.setTexture(m_SpriteSheet);
		m_CurrentFrame = { frameSize.x * startFrameCoordinates.x, frameSize.y * startFrameCoordinates.y, frameSize.x, frameSize.y };
		//spdlog::info("x:" << std::to_string(m_CurrentFrame.top) << "y:" <<)
		//m_Sprite.setTextureRect(m_CurrentFrame);
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


	void Animation::setPosition(float x, float y)
	{
		m_Sprite.setPosition(x, y);
	}


	sf::Vector2f Animation::getPosition() const
	{
		return m_Sprite.getPosition();
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

	void Animation::update(const sf::Time& dt)
	{

	}

	void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite);
	}

	void Animation::handleEvent(const sf::Event& event)
	{

	}
}