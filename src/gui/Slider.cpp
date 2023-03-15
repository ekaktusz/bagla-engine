#include "gui/Slider.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace bgl
{
	Slider::Slider() : m_Progress(0.5)
	{
		m_OuterSlider.setFillColor(sf::Color::Black);
		m_OuterSlider.setOutlineColor(sf::Color::White);
		m_OuterSlider.setOutlineThickness(1);

		m_InnerSlider.setFillColor(sf::Color::White);
		m_Indicator.setFillColor(sf::Color::Red);
	}

	void Slider::update(const sf::Time& dt)
	{
		
	}

	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_OuterSlider);
		target.draw(m_InnerSlider);
		target.draw(m_Indicator);
	}

	void Slider::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (m_OuterSlider.getGlobalBounds().contains(
				sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
			{
				m_Progress = std::abs(m_OuterSlider.getPosition().x - event.mouseButton.x) / m_OuterSlider.getSize().x;
			}
		}
	}

	void Slider::setSize(sf::Vector2f size)
	{
		m_OuterSlider.setSize(size);
		m_InnerSlider.setSize(size - sf::Vector2f(4, 4));
		m_Indicator.setSize({ 5, size.y });
	}

	void Slider::setPosition(sf::Vector2f position)
	{
		m_OuterSlider.setPosition(position);
		m_InnerSlider.setPosition(position + sf::Vector2f(2, 2));
	}

}