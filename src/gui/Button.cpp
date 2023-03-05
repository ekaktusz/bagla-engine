#include "gui/Button.h"
#include <SFML/Window/Event.hpp>
#include <spdlog/spdlog.h>
#include <SFML/Graphics/RenderTarget.hpp>

namespace bgl
{
	Button::Button() :
		m_Text(),
		m_Position(),
		m_Size{100, 100},
		m_ActionToDo(),
		m_FillColor(sf::Color::Black),
		m_OutlineColor(sf::Color::White),
		m_TextColor(sf::Color::White),
		m_OutlineThickness(1)
	{
		flushChanges();
	}
	
	Button::Button(const std::string& buttonString, sf::Vector2f position, sf::Vector2f size, std::function<void()> actionToDo) :
		m_Text(),
		m_Position(position),
		m_Size(size),
		m_ActionToDo(actionToDo),
		m_FillColor(sf::Color::Black),
		m_OutlineColor(sf::Color::White),
		m_TextColor(sf::Color::White),
		m_OutlineThickness(1)
	{
		flushChanges();
	}

	void Button::setString(const std::string& buttonString)
	{
		m_Text.setString(buttonString);
	}

	void Button::setActionTodo(std::function<void()> actionToDo)
	{
		m_ActionToDo = actionToDo;
	}

	void Button::setPosition(sf::Vector2f position)
	{
		m_Position = position;
	}

	void Button::setSize(sf::Vector2f size)
	{
		m_Size = size;
	}

	void Button::setFillColor(sf::Color color)
	{
		m_FillColor = color;
	}

	void Button::setOutlineColor(sf::Color color)
	{
		m_OutlineColor = color;
	}

	void Button::setOutlineThickness(float thickness)
	{
		m_OutlineThickness = thickness;
	}

	void Button::setTextColor(sf::Color color)
	{
		m_Text.setFillColor(color);
	}

	void Button::setFont(const sf::Font& font)
	{
		m_Text.setFont(font);
	}

	void Button::update(const sf::Time& dt)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_OuterButton);
		target.draw(m_InnerButton);
		target.draw(m_Text);
	}

	void Button::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (m_OuterButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				if (m_ActionToDo)
				{
					m_ActionToDo();
				}
				else
				{
					spdlog::warn("Button pressed, but no action set to it!");
				}
			}
		}
	}

	void Button::setTextAlignment()
	{
		sf::Vector2f center{ m_Text.getGlobalBounds().width / 2.f, m_Text.getGlobalBounds().height / 2.f };
		sf::Vector2f localBounds{ center.x + m_Text.getLocalBounds().left, center.y + m_Text.getLocalBounds().top };
		sf::Vector2f rounded{ std::round(localBounds.x), std::round(localBounds.y) };
		m_Text.setOrigin(rounded);
	}

	void Button::flushChanges()
	{
		setTextAlignment();

		m_InnerButton.setSize(m_Size);
		m_OuterButton.setSize({ m_Size.x + m_OutlineThickness * 2, m_Size.y + m_OutlineThickness * 2 });

		m_InnerButton.setPosition(m_Position);
		m_OuterButton.setPosition(m_Position.x - m_OutlineThickness, m_Position.y - m_OutlineThickness);

		m_InnerButton.setFillColor(m_FillColor);
		m_OuterButton.setOutlineColor(m_OutlineColor);
		
		m_Text.setPosition(m_InnerButton.getPosition().x + m_InnerButton.getSize().x / 2, m_InnerButton.getPosition().y + m_InnerButton.getSize().y / 2);
	}

}

