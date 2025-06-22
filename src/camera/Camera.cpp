#include "camera/Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace bgl
{
Camera::Camera(sf::RenderWindow& renderWindow) : _view(sf::Vector2f(0.f, 0.f), static_cast<sf::Vector2f>(renderWindow.getSize())) {}

Camera::~Camera() {}

void Camera::setWorldBoundaries(float x, float y, float w, float h)
{
	_worldBoundaries = { x, y, w, h };
}

void Camera::setWorldBoundaries(sf::FloatRect boundaries)
{
	_worldBoundaries = boundaries;
}

sf::FloatRect Camera::getWorldBoundaries() const
{
	return _worldBoundaries;
}

void Camera::setPosition(float x, float y)
{
	// Adjust position to ensure the camera stays within the world boundaries
	const float halfWidth = _view.getSize().x / 2.f;
	const float halfHeight = _view.getSize().y / 2.f;

	const float newX = std::max(_worldBoundaries.left + halfWidth, std::min(x + halfWidth, _worldBoundaries.left + _worldBoundaries.width - halfWidth)) - halfWidth;
	const float newY = std::max(_worldBoundaries.top + halfHeight, std::min(y + halfHeight, _worldBoundaries.top + _worldBoundaries.height - halfHeight)) - halfHeight;

	_view.setCenter(x + halfWidth, y + halfHeight);
	flush();
}

void Camera::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

sf::Vector2f Camera::getPosition() const
{
	return { _view.getCenter().x - _view.getSize().x / 2.f, _view.getCenter().y - _view.getSize().y / 2.f };
}

void Camera::setCenterPosition(float x, float y)
{
	// Adjust position to ensure the camera stays within the world boundaries
	const float halfWidth = _view.getSize().x / 2.f;
	const float halfHeight = _view.getSize().y / 2.f;

	const float newX = std::max(_worldBoundaries.left + halfWidth, std::min(x, _worldBoundaries.left + _worldBoundaries.width - halfWidth));
	const float newY = std::max(_worldBoundaries.top + halfHeight, std::min(y, _worldBoundaries.top + _worldBoundaries.height - halfHeight));

	_view.setCenter(newX, newY);
	flush();
}

void Camera::setCenterPosition(sf::Vector2f position)
{
	setCenterPosition(position.x, position.y);
}

sf::Vector2f Camera::getCenterPosition() const
{
	return _view.getCenter();
}

void Camera::setScale(float scale)
{
	_view.zoom(scale);
	flush();
}

void Camera::setAngle(float angle)
{
	_view.setRotation(angle);
	flush();
}

float Camera::getAngle() const
{
	return _view.getRotation();
}

void Camera::move(sf::Vector2f movement)
{
	sf::Vector2f newPosition = _view.getCenter() + movement;
	setCenterPosition(newPosition);
}

void Camera::attach(sf::RenderWindow& renderWindow)
{
	_attachedRenderWindow = &renderWindow;
}

void Camera::flush()
{
	_attachedRenderWindow->setView(_view);
}
}