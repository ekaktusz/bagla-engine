#pragma once

#include "gui/Widget.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

namespace sf
{
	class RenderWindow;
};

namespace bgl
{
	class Slider : public Widget
	{
	public:
		Slider(const sf::RenderWindow& renderWindow);

		void update(const sf::Time& dt) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void handleEvent(const sf::Event& event) override;

		float getProgress() const;

		void setSize(sf::Vector2f size);
		void setPosition(sf::Vector2f position);

		void setOnProgressChange(std::function<void(float)> onProgressChange) { m_OnProgressChange = onProgressChange; }
		
 
	private:
		const sf::RenderWindow& m_RenderWindow;

		float m_Progress; // between 0 and 1

		sf::RectangleShape m_OuterSlider;
		sf::RectangleShape m_InnerSlider;
		sf::RectangleShape m_Indicator;

		std::function<void(float)> m_OnProgressChange;
	};
}