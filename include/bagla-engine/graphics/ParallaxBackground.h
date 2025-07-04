#pragma once

#include "GameObject.h"
#include "graphics/ParallaxLayer.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include <memory>
#include <optional>
#include <vector>

namespace bgl
{
class Camera;

class ParallaxBackground : public GameObject, public sf::Drawable
{
public:
	ParallaxBackground() = default;

	std::optional<sf::FloatRect> getGlobalBounds() const;

	void setPosition(sf::Vector2f position);
	void setScale(sf::Vector2f scale);

	void attachToCamera(Camera& camera);

	void update(const sf::Time& dt) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void addLayer(std::unique_ptr<ParallaxLayer> parallaxLayer);

private:
	std::vector<std::unique_ptr<ParallaxLayer>> _parallaxLayers;

	Camera* _attachedCamera;
};
}