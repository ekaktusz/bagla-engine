#include "gui/CheckBox.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>

namespace bgl
{
CheckBox::CheckBox(const sf::RenderWindow& renderWindow) : _renderWindow(renderWindow), _checked(false), _outlineThickness(1)
{
	// Default colors for now
	_checkedColor = sf::Color::Red;
	_uncheckedColor = sf::Color::Black;
	_outlineColor = sf::Color::White;

	_checkBoxShape.setFillColor(_uncheckedColor);
	_checkBoxShape.setOutlineColor(_outlineColor);
	_checkBoxShape.setOutlineThickness(_outlineThickness);
}

CheckBox::~CheckBox() {}

void CheckBox::update(const sf::Time& dt)
{
	//_checked ? _checkBoxShape.setFillColor(_checkedColor) : _checkBoxShape.setFillColor(_uncheckedColor);
}

void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_checkBoxShape);
	if (_checked)
		drawCheckMark(target);
}

void CheckBox::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (_checkBoxShape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
		{
			_checked = !_checked;
		}
	}
}

void CheckBox::setSize(float s)
{
	_checkBoxShape.setSize({ s, s });
}

void CheckBox::setPosition(sf::Vector2f position)
{
	_checkBoxShape.setPosition(position);
}

void CheckBox::setUncheckedColor(sf::Color color)
{
	_uncheckedColor = color;
}

void CheckBox::setOutlineColor(sf::Color color)
{
	_outlineColor = color;
	_checkBoxShape.setOutlineColor(color);
}

void CheckBox::setCheckedColor(sf::Color color)
{
	_checkedColor = color;
}

void CheckBox::setOutlineThickness(float thickness)
{
	_outlineThickness = thickness;
	_checkBoxShape.setOutlineThickness(thickness);
}

void CheckBox::drawCheckMark(sf::RenderTarget& target) const
{
	sf::RectangleShape line1({ std::sqrt(2.f) * _checkBoxShape.getSize().x, 1 });
	line1.setPosition(_checkBoxShape.getPosition());
	line1.rotate(45);
	line1.setFillColor(sf::Color::White);
	line1.setOutlineThickness(1);
	line1.setOutlineColor(sf::Color::White);
	sf::RectangleShape line2({ std::sqrt(2.f) * _checkBoxShape.getSize().x, 1 });
	line2.setPosition(_checkBoxShape.getPosition().x, _checkBoxShape.getPosition().y + _checkBoxShape.getSize().y);
	line2.rotate(-45);
	line2.setFillColor(sf::Color::White);
	line2.setOutlineThickness(1);
	line2.setOutlineColor(sf::Color::White);

	target.draw(line1);
	target.draw(line2);
}

}