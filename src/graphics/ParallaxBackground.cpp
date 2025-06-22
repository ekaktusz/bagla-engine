#include "graphics/ParallaxBackground.h"

#include "camera/Camera.h"

#include <spdlog/spdlog.h>

namespace bgl
{
std::optional<sf::FloatRect> ParallaxBackground::getGlobalBounds() const
{
	if (_parallaxLayers.empty())
	{
		SPDLOG_ERROR("empty parallax background, bounds are undefined");
		return std::nullopt;
	}

	return _parallaxLayers.front()->getGlobalBounds();
}

void ParallaxBackground::setPosition(sf::Vector2f position)
{
	for (auto& parallaxLayer : _parallaxLayers)
	{
		parallaxLayer->setPosition(position);
	}
}

void ParallaxBackground::setScale(sf::Vector2f scale)
{
	for (auto& parallaxLayer : _parallaxLayers)
	{
		parallaxLayer->setScale(scale);
	}
}

void ParallaxBackground::attachToCamera(Camera& camera)
{
	_attachedCamera = &camera;
}

void ParallaxBackground::update(const sf::Time& dt)
{
	if (_attachedCamera == nullptr)
		return;

	const sf::Vector2f cameraPosition = _attachedCamera->getPosition();

	for (auto& parallaxLayer : _parallaxLayers)
	{
		parallaxLayer->update(cameraPosition);
	}
}

void ParallaxBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//throw std::logic_error("The method or operation is not implemented.");
	for (const auto& parallaxLayer : _parallaxLayers)
	{
		target.draw(*parallaxLayer);
	}
}

void ParallaxBackground::addLayer(std::unique_ptr<ParallaxLayer> parallaxLayer)
{
	_parallaxLayers.push_back(std::move(parallaxLayer));
}

}
