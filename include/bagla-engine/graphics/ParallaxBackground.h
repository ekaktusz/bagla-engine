#pragma once

#include "GameObject.h"
#include "graphics/ParallaxLayer.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

#include <optional>

namespace bgl
{
	class ParallaxBackground : public GameObject
	{
	public:

		ParallaxBackground() = default;

		std::optional<sf::FloatRect> getGlobalBounds() const;

		void setPosition(sf::Vector2f position);
		void setScale(sf::Vector2f scale);

		void update(const sf::Time& dt) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void handleEvent(const sf::Event& event) override;

		void addLayer(const ParallaxLayer& parallaxLayer);

	private:
		std::vector<ParallaxLayer> m_ParallaxLayers;
	};
}