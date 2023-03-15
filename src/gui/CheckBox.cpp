#include "gui/CheckBox.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace bgl
{
	CheckBox::CheckBox(const sf::RenderWindow& renderWindow) : m_RenderWindow(renderWindow), m_Checked(false), m_OutlineThickness(1)
	{
		// Default colors for now
		m_CheckedColor = sf::Color::Red;
		m_UncheckedColor = sf::Color::Black;
		m_OutlineColor = sf::Color::White;

		m_CheckBoxShape.setOutlineColor(m_OutlineColor);
		m_CheckBoxShape.setOutlineThickness(m_OutlineThickness);
	}

	CheckBox::~CheckBox()
	{

	}

	void CheckBox::update(const sf::Time& dt)
	{
		m_Checked ? m_CheckBoxShape.setFillColor(m_CheckedColor) : m_CheckBoxShape.setFillColor(m_UncheckedColor);
	}

	void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_CheckBoxShape);
	}

	void CheckBox::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (m_CheckBoxShape.getGlobalBounds().contains(
				sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
			{
				m_Checked = !m_Checked;
			}
		}
	}

	void CheckBox::setSize(float s)
	{
		m_CheckBoxShape.setSize({ s,s });
	}

	void CheckBox::setPosition(sf::Vector2f position)
	{
		m_CheckBoxShape.setPosition(position);
	}

	void CheckBox::setUncheckedColor(sf::Color color)
	{
		m_UncheckedColor = color;
	}

	void CheckBox::setOutlineColor(sf::Color color)
	{
		m_OutlineColor = color;
		m_CheckBoxShape.setOutlineColor(color);
	}

	void CheckBox::setCheckedColor(sf::Color color)
	{
		m_CheckedColor = color;
	}

	void CheckBox::setOutlineThickness(float thickness)
	{
		m_OutlineThickness = thickness;
		m_CheckBoxShape.setOutlineThickness(thickness);
	}
}