#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>

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
		
		void setScale(float scale);
		float getScale() const;

		void setAngle(float angle);
		float getAngle() const;

		void update(const sf::Time& dt);
		
	private:
		sf::View m_View;
		sf::RenderWindow& m_AttachedRenderWindow;
		sf::FloatRect m_WorldBoundaries;
	};

}