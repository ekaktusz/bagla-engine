#include "gui/Slider.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "gui/FocusLock.h"
#include "MathExtensions.h"
#include <cmath>
#include <spdlog/spdlog.h>

namespace bgl
{
	Slider::Slider(const sf::RenderWindow& renderWindow) : m_RenderWindow(renderWindow), m_Progress(0.5)
	{
		m_OuterSlider.setFillColor(sf::Color::Black);
		m_OuterSlider.setOutlineColor(sf::Color::White);
		m_OuterSlider.setOutlineThickness(1);

		m_InnerSlider.setFillColor(sf::Color::White);
		m_Indicator.setFillColor(sf::Color::Red);

		m_Text.setString("");
		m_Text.setFillColor(sf::Color::White);
		m_Text.setOutlineColor(sf::Color::Black);
		m_Text.setOutlineThickness(1);
	}

	void Slider::update(const sf::Time& dt)
	{
		m_Indicator.setPosition(m_OuterSlider.getPosition().x + m_Progress * m_OuterSlider.getSize().x, m_OuterSlider.getPosition().y);
		m_InnerSlider.setSize({ (m_OuterSlider.getSize().x - 4) * m_Progress, m_InnerSlider.getSize().y });

		updateTextPosition();

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
			if (m_OnProgressChange)
			{
				m_OnProgressChange(m_Progress);
			}
		}
	}

	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_OuterSlider);
		target.draw(m_InnerSlider);
		target.draw(m_Indicator);
		if (m_Text.getString() != "")
		{
			target.draw(m_Text);
		}
	}

	void Slider::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonReleased && FocusLock::isWidgetInFocus(this))
		{
			FocusLock::unlockFocus();
		}
	}

	float Slider::getProgress() const
	{
		return m_Progress;
	}

	void Slider::setProgress(float progress)
	{
		if (progress > 1 || progress < 0)
		{
			spdlog::warn("not valid progress: " + std::to_string(progress));
			return;
		}
		m_Progress = progress;
		if (m_OnProgressChange)
		{
			m_OnProgressChange(m_Progress);
		}
	}

	void Slider::setSize(sf::Vector2f size)
	{
		m_OuterSlider.setSize(size);
		m_InnerSlider.setSize(size - sf::Vector2f(4, 4));
		m_Indicator.setSize({ 5, size.y });

		m_Text.setCharacterSize(m_InnerSlider.getSize().y);
	}

	void Slider::setPosition(sf::Vector2f position)
	{
		m_OuterSlider.setPosition(position);
		m_InnerSlider.setPosition(position + sf::Vector2f(2, 2));
	}

	void Slider::updateTextPosition()
	{
		sf::Vector2f center{ m_Text.getGlobalBounds().width / 2.f, m_Text.getGlobalBounds().height / 2.f };
		sf::Vector2f localBounds{ center.x + m_Text.getLocalBounds().left, center.y + m_Text.getLocalBounds().top };
		sf::Vector2f rounded{ std::round(localBounds.x), std::round(localBounds.y) };
		m_Text.setOrigin(rounded);
		m_Text.setPosition(m_OuterSlider.getPosition().x + m_OuterSlider.getSize().x / 2, m_InnerSlider.getPosition().y + m_InnerSlider.getSize().y / 2);
	}

	void Slider::setFont(const sf::Font& font)
	{
		m_Text.setFont(font);
	}

	void Slider::setString(const std::string& str)
	{
		m_Text.setString(str);
	}

}