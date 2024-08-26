#pragma once

#include "graphics/ParallaxLayer.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

#include <SFML/System/Time.hpp>

#include <optional>

#include <memory>

namespace bgl
{
	class Camera;

	class ParallaxBackground : public sf::Drawable
	{
	public:

		ParallaxBackground() = default;

		std::optional<sf::FloatRect> getGlobalBounds() const;

		void setPosition(sf::Vector2f position);
		void setScale(sf::Vector2f scale);

		void attachToCamera(Camera& camera);

		void update(const sf::Time& dt);
		
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void addLayer(std::unique_ptr<ParallaxLayer> parallaxLayer);

	private:
		std::vector<std::unique_ptr<ParallaxLayer>> m_ParallaxLayers;

		Camera* m_attachedCamera;
	};
}