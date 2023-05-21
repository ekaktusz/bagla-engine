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
		m_View.setCenter(x + m_View.getSize().x / 2.f, y + m_View.getSize().x / 2.f);
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
		m_View.setCenter(x, y);
		flush();
	}

	void Camera::setCenterPosition(sf::Vector2f position)
	{
		m_View.setCenter(position);
		flush();
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
		m_View.move(movement);
		flush();
	}

	void Camera::flush()
	{
		m_AttachedRenderWindow.setView(m_View);
	}
}