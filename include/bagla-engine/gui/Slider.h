#pragma once

#include "gui/Widget.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace bgl
{
	class Slider : public Widget
	{
	public:
		Slider();

		void update(const sf::Time& dt) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void handleEvent(const sf::Event& event) override;

		void setSize(sf::Vector2f size);
		void setPosition(sf::Vector2f position);
 
	private:
		float m_Progress; // between 0 and 1

		sf::RectangleShape m_OuterSlider;
		sf::RectangleShape m_InnerSlider;
		sf::RectangleShape m_Indicator;
	};
}