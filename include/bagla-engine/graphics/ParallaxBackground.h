#pragma once

#include "GameObject.h"
#include "graphics/ParallaxLayer.h"

#include <spdlog/spdlog.h>

#include <SFML/Graphics/RenderTarget.hpp>

#include <exception>

namespace bgl
{
	class ParallaxBackground : public GameObject
	{
	public:

		ParallaxBackground() = default;

		const sf::FloatRect& getGlobalBounds() const;

		void setPosition(sf::Vector2f position);
		void setScale(sf::Vector2f scale);

		void update(const sf::Time& dt) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void handleEvent(const sf::Event& event);

		void addLayer(const ParallaxLayer& parallaxLayer);

	private:
		std::vector<ParallaxLayer> m_ParallaxLayers;
	};
}