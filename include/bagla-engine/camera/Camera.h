#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
class Time;
class RenderWindow;
}

namespace bgl
{
class Camera
{
public:
	Camera(sf::RenderWindow& renderWindow);
	~Camera();

	void setWorldBoundaries(float x, float y, float w, float h);
	void setWorldBoundaries(sf::FloatRect boundaries);
	sf::FloatRect getWorldBoundaries() const;

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;

	void setCenterPosition(float x, float y);
	void setCenterPosition(sf::Vector2f position);
	sf::Vector2f getCenterPosition() const;

	void setScale(float scale);
	float getScale() const;

	void setAngle(float angle);
	float getAngle() const;

	void move(sf::Vector2f movement);

	void attach(sf::RenderWindow& renderWindow);

private:
	void flush();

private:
	sf::RenderWindow* _attachedRenderWindow = nullptr;
	sf::View _view;
	sf::FloatRect _worldBoundaries;
};

}