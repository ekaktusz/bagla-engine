#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "GameObject.h"

namespace bgl
{
	class ParallaxLayer : public GameObject
	{
	public:
		explicit ParallaxLayer(const sf::Texture& backgroundTexture)
			: m_Texture(backgroundTexture)
		{
			m_Sprite.setTexture(backgroundTexture);
			m_Sprite.setPosition(0.f, 0.f);
		}

		void update(const sf::Time& dt) override
		{
			//throw std::logic_error("The method or operation is not implemented.");
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(m_Sprite);
		}

		void handleEvent(const sf::Event& event) override
		{
			
		}

		void setPosition(sf::Vector2f position) 
		{
			m_Sprite.setPosition(position);
		}

		void setScale(sf::Vector2f scale) 
		{
			m_Sprite.setScale(scale);
		}

		const sf::FloatRect& getGlobalBounds() const
		{
			return m_Sprite.getGlobalBounds();
		}

	private:
		sf::Sprite m_Sprite;
		sf::Texture m_Texture;
	};
}