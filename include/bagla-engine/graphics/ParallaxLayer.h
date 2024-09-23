#pragma once

#include "GameObject.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace bgl
{
class ParallaxLayer : public sf::Drawable
{
public:
	ParallaxLayer(const sf::Texture& backgroundTexture, float distanceFromCamera, float offsetY = 0.f);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Vector2f cameraPosition);
	void setScale(sf::Vector2f scale);
	void setPosition(sf::Vector2f position);

	sf::FloatRect getGlobalBounds() const;

private:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	sf::Shader m_ParallaxShader;

	float m_DistanceFromCamera;
	float m_OffsetY;
};
}