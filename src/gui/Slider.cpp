#include "gui/Slider.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "gui/FocusLock.h"
#include "MathExtensions.h"

namespace bgl
{
	Slider::Slider(const sf::RenderWindow& renderWindow) : m_RenderWindow(renderWindow), m_Progress(0.5)
	{
		m_OuterSlider.setFillColor(sf::Color::Black);
		m_OuterSlider.setOutlineColor(sf::Color::White);
		m_OuterSlider.setOutlineThickness(1);

		m_InnerSlider.setFillColor(sf::Color::White);
		m_Indicator.setFillColor(sf::Color::Red);
	}

	void Slider::update(const sf::Time& dt)
	{
		m_Indicator.setPosition(m_OuterSlider.getPosition().x + m_Progress * m_OuterSlider.getSize().x, m_OuterSlider.getPosition().y);
		m_InnerSlider.setSize({ (m_OuterSlider.getSize().x - 4) * m_Progress, m_InnerSlider.getSize().y });

		sf::Vector2i mousePosition = sf::Mouse::getPosition(m_RenderWindow);
		if (m_OuterSlider.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!FocusLock::isLocked())
				{
					FocusLock::lockFocus(this);
				}
			}
		}

		if (FocusLock::isWidgetInFocus(this))
		{
			m_Progress = mid(0.f, (mousePosition.x - m_OuterSlider.getPosition().x) / m_OuterSlider.getSize().x, 1.f);
		}
	}

	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_OuterSlider);
		target.draw(m_InnerSlider);
		target.draw(m_Indicator);
	}

	void Slider::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonReleased && FocusLock::isWidgetInFocus(this))
		{
			FocusLock::unlockFocus();
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