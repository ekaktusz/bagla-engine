#pragma once

#include "GameObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace bgl
{
	class ParallaxBackground : public GameObject
	{
	public:

		ParallaxBackground() = default;

		void initialize(const sf::Texture& backgroundTexture)
		{
			m_Texture = backgroundTexture;
			m_Sprite.setTexture(backgroundTexture);
			m_Sprite.setPosition(0.f, 0.f);
		}

		void setScale(sf::Vector2f scale)
		{
			m_Sprite.setScale(scale);
		}

		const sf::FloatRect& getGlobalBounds() 
		{
			return m_Sprite.getGlobalBounds();
		}

		void setPosition(sf::Vector2f position)
		{
			m_Sprite.setPosition(position);
		}

		void update(const sf::Time& dt) override
		{
			//throw std::logic_error("The method or operation is not implemented.");
		}


		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			//throw std::logic_error("The method or operation is not implemented.");
			target.draw(m_Sprite);
		}


		void handleEvent(const sf::Event& event) override
		{
			//throw std::logic_error("The method or operation is not implemented.");
		}

	private:
		sf::Sprite m_Sprite;
		sf::Texture m_Texture;
	};
}