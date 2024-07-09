#include "camera/Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace bgl
{
	Camera::Camera(sf::RenderWindow& renderWindow) :
		m_AttachedRenderWindow(renderWindow),
		m_View(sf::Vector2f(0.f, 0.f), static_cast<sf::Vector2f>(renderWindow.getSize()))
	{
		m_AttachedRenderWindow.setView(m_View);
	}

	Camera::~Camera()
	{

	}

	void Camera::setWorldBoundaries(float x, float y, float w, float h)
	{
		m_WorldBoundaries = { x, y, w, h };
	}

	void Camera::setWorldBoundaries(sf::FloatRect boundaries)
	{
		m_WorldBoundaries = boundaries;
	}

	sf::FloatRect Camera::getWorldBoundaries() const
	{
		return m_WorldBoundaries;
	}

	void Camera::setPosition(float x, float y)
	{
		// Adjust position to ensure the camera stays within the world boundaries
        const float halfWidth = m_View.getSize().x / 2.f;
        const float halfHeight = m_View.getSize().y / 2.f;

        const float newX = std::max(m_WorldBoundaries.left + halfWidth, std::min(x + halfWidth, m_WorldBoundaries.left + m_WorldBoundaries.width - halfWidth)) - halfWidth;
        const float newY = std::max(m_WorldBoundaries.top + halfHeight, std::min(y + halfHeight, m_WorldBoundaries.top + m_WorldBoundaries.height - halfHeight)) - halfHeight;

        m_View.setCenter(x + halfWidth, y + halfHeight);
		flush();
	}

	void Camera::setPosition(sf::Vector2f position)
	{
		setPosition(position.x, position.y);
	}

	sf::Vector2f Camera::getPosition() const
	{
		return { m_View.getCenter().x + m_View.getSize().x / 2.f,  m_View.getCenter().y + m_View.getSize().y / 2.f };
	}

	void Camera::setCenterPosition(float x, float y)
	{
		// Adjust position to ensure the camera stays within the world boundaries
        const float halfWidth = m_View.getSize().x / 2.f;
        const float halfHeight = m_View.getSize().y / 2.f;

        const float newX = std::max(m_WorldBoundaries.left + halfWidth, std::min(x, m_WorldBoundaries.left + m_WorldBoundaries.width - halfWidth));
        const float newY = std::max(m_WorldBoundaries.top + halfHeight, std::min(y, m_WorldBoundaries.top + m_WorldBoundaries.height - halfHeight));

        m_View.setCenter(newX, newY);
		flush();
	}

	void Camera::setCenterPosition(sf::Vector2f position)
	{
		setCenterPosition(position.x, position.y);
	}

	sf::Vector2f Camera::getCenterPosition() const
	{
		return m_View.getCenter();
	}

	void Camera::setScale(float scale)
	{
		m_View.zoom(scale);
		flush();
	}

	void Camera::setAngle(float angle)
	{
		m_View.setRotation(angle);
		flush();
	}

	float Camera::getAngle() const
	{
		return m_View.getRotation();
	}

	void Camera::move(sf::Vector2f movement)
	{
		sf::Vector2f newPosition = m_View.getCenter() + movement;
        setCenterPosition(newPosition);
	}

	void Camera::flush()
	{
		m_AttachedRenderWindow.setView(m_View);
	}
}