#include "gui/Button.h"
#include <SFML/Window/Event.hpp>
#include <spdlog/spdlog.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include <gui/FocusLock.h>

namespace bgl
{
	Button::Button(const sf::RenderWindow& renderWindow) :
		m_RenderWindow(renderWindow),
		m_Text(),
		m_Position(),
		m_Size{100, 100},
		m_ActionToDo(),
		m_FillColor(sf::Color::Black),
		m_OutlineColor(sf::Color::White),
		m_TextColor(sf::Color::White),
		m_HoverColor{48, 48, 48},
		m_OutlineThickness(1)
	{
		initializeInnerButton();
	}
	
	Button::Button(const sf::RenderWindow& renderWindow, const std::string& buttonString, sf::Vector2f position, sf::Vector2f size, std::function<void()> actionToDo) :
		m_RenderWindow(renderWindow),
		m_Text(),
		m_Position(position),
		m_Size(size),
		m_ActionToDo(actionToDo),
		m_FillColor(sf::Color::Black),
		m_OutlineColor(sf::Color::White),
		m_TextColor(sf::Color::White),
		m_HoverColor{ 48, 48, 48 },
		m_OutlineThickness(1)
	{
		initializeInnerButton();
	}

	void Button::setString(const std::string& buttonString)
	{
		m_Text.setString(buttonString);
		refreshTextOrigin();
	}

	void Button::setActionTodo(std::function<void()> actionToDo)
	{
		m_ActionToDo = actionToDo;
	}

	void Button::setPosition(sf::Vector2f position)
	{
		m_Position = position;
		m_InnerButton.setPosition(position);
		refreshTextPosition();
	}

	void Button::setSize(sf::Vector2f size)
	{
		m_Size = size;
		m_InnerButton.setSize(size);
		refreshTextPosition();
	}

	void Button::setFillColor(sf::Color color)
	{
		m_FillColor = color;
		m_InnerButton.setFillColor(m_FillColor);
	}

	void Button::setOutlineColor(sf::Color color)
	{
		m_OutlineColor = color;
		m_InnerButton.setOutlineColor(m_OutlineColor);
	}

	void Button::setOutlineThickness(float thickness)
	{
		m_OutlineThickness = thickness;
		m_InnerButton.setOutlineThickness(m_OutlineThickness);
	}

	void Button::setTextColor(sf::Color color)
	{
		m_Text.setFillColor(color);
	}

	void Button::setFont(const sf::Font& font)
	{
		m_Text.setFont(font);
	}

	void Button::setHoverColor(sf::Color color)
	{
		m_HoverColor = color;
	}

	void Button::update(const sf::Time& dt)
	{
		m_InnerButton.setFillColor(m_FillColor);
		sf::Vector2i mousePosition = sf::Mouse::getPosition(m_RenderWindow);
		if (m_InnerButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			m_InnerButton.setFillColor(m_HoverColor);
		}
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_InnerButton);
		target.draw(m_Text);
	}

	void Button::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (m_InnerButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				if (m_ActionToDo)
				{
					m_ActionToDo();
				}
				else
				{
					spdlog::warn("Button is clicked, but no action set.");
				}
			}
		}
	}

	void Button::setSoundOnSelect(const sf::SoundBuffer& soundBuffer)
	{
		m_SoundOnSelect.setBuffer(soundBuffer);
	}

	void Button::setSoundOnHover(const sf::SoundBuffer& soundBuffer)
	{
		m_SoundOnHover.setBuffer(soundBuffer);
	}

	void Button::refreshTextOrigin()
	{
		sf::Vector2f center{ m_Text.getGlobalBounds().width / 2.f, m_Text.getGlobalBounds().height / 2.f };
		sf::Vector2f localBounds{ center.x + m_Text.getLocalBounds().left, center.y + m_Text.getLocalBounds().top };
		sf::Vector2f rounded{ std::round(localBounds.x), std::round(localBounds.y) };
		m_Text.setOrigin(rounded);
	}

	void Button::refreshTextPosition()
	{
		m_Text.setPosition(m_InnerButton.getPosition().x + m_InnerButton.getSize().x / 2, m_InnerButton.getPosition().y + m_InnerButton.getSize().y / 2);
	}

	void Button::initializeInnerButton()
	{
		m_InnerButton.setFillColor(m_FillColor);
		m_InnerButton.setOutlineColor(m_OutlineColor);
		m_InnerButton.setOutlineThickness(m_OutlineThickness);
		m_InnerButton.setPosition(m_Position);
		m_InnerButton.setSize(m_Size);
	}

}

