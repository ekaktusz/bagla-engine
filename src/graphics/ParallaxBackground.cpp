#include "graphics/ParallaxBackground.h"

#include "camera/Camera.h"

#include <spdlog/spdlog.h>

namespace bgl
{
	std::optional<sf::FloatRect> ParallaxBackground::getGlobalBounds() const
	{
		if (m_ParallaxLayers.empty())
		{
			spdlog::error("empty parallax background, bounds are undefined");
			return std::nullopt;
		}

		return m_ParallaxLayers.front()->getGlobalBounds();
	}

	void ParallaxBackground::setPosition(sf::Vector2f position)
	{
		for (auto& parallaxLayer : m_ParallaxLayers)
		{
			parallaxLayer->setPosition(position);
		}
	}

	void ParallaxBackground::setScale(sf::Vector2f scale)
	{
		for (auto& parallaxLayer : m_ParallaxLayers)
		{
			parallaxLayer->setScale(scale);
		}
	}

	void ParallaxBackground::attachToCamera(Camera& camera)
	{
		m_attachedCamera = &camera;
	}

	void ParallaxBackground::update(const sf::Time& dt)
	{
		if (m_attachedCamera == nullptr) return;

		const sf::Vector2f cameraPosition = m_attachedCamera->getPosition();

		for (auto& parallaxLayer : m_ParallaxLayers)
		{
			parallaxLayer->update(cameraPosition);
		}
	}

	void ParallaxBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//throw std::logic_error("The method or operation is not implemented.");
		for (const auto& parallaxLayer : m_ParallaxLayers)
		{
			target.draw(*parallaxLayer);
		}
	}


	void ParallaxBackground::addLayer(std::unique_ptr<ParallaxLayer> parallaxLayer)
	{
		m_ParallaxLayers.push_back(std::move(parallaxLayer));
	}

}

