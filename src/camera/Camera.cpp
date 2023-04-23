#include "camera/Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace bgl
{
	Camera::Camera(sf::RenderWindow& renderWindow) : m_AttachedRenderWindow(renderWindow)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::setWorldBoundaries(float x, float y, float w, float h)
	{

	}

	void Camera::setWorldBoundaries(sf::FloatRect boundaries)
	{

	}

	sf::FloatRect Camera::getWorldBoundaries() const
	{
		return { 0, 0, 0, 0 };
	}

	void Camera::setPosition(float x, float y)
	{

	}

	void Camera::setPosition(sf::Vector2f position)
	{

	}

	sf::Vector2f Camera::getPosition() const
	{
		return { 0, 0 };
	}

	void Camera::setScale(float scale)
	{

	}

	void Camera::setAngle(float angle)
	{

	}

	float Camera::getAngle() const
	{
		return 0.f;
	}

	void Camera::update(const sf::Time& dt)
	{

	}

}