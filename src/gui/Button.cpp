#include "gui/Button.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <functional>
#include <spdlog/spdlog.h>
#include <string>

namespace bgl
{
Button::Button(const sf::RenderWindow& renderWindow) :
	_renderWindow(renderWindow),
	_text(),
	_position(),
	_size { 100, 100 },
	_actionToDo(),
	_fillColor(sf::Color::Black),
	_outlineColor(sf::Color::White),
	_textColor(sf::Color::White),
	_hoverColor { 48, 48, 48 },
	_outlineThickness(1)
{
	initializeInnerButton();
}

Button::Button(const sf::RenderWindow& renderWindow, const std::string& buttonString, sf::Vector2f position, sf::Vector2f size, std::function<void()> actionToDo) :
	_renderWindow(renderWindow),
	_text(),
	_position(position),
	_size(size),
	_actionToDo(actionToDo),
	_fillColor(sf::Color::Black),
	_outlineColor(sf::Color::White),
	_textColor(sf::Color::White),
	_hoverColor { 48, 48, 48 },
	_outlineThickness(1)
{
	initializeInnerButton();
}

void Button::setString(const std::string& buttonString)
{
	_text.setString(buttonString);
	refreshTextOrigin();
}

void Button::setActionTodo(std::function<void()> actionToDo)
{
	_actionToDo = actionToDo;
}

void Button::setPosition(sf::Vector2f position)
{
	_position = position;
	_innerButton.setPosition(position);
	refreshTextPosition();
}

void Button::setSize(sf::Vector2f size)
{
	_size = size;
	_innerButton.setSize(size);
	refreshTextPosition();
}

void Button::setFillColor(sf::Color color)
{
	_fillColor = color;
	_innerButton.setFillColor(_fillColor);
}

void Button::setOutlineColor(sf::Color color)
{
	_outlineColor = color;
	_innerButton.setOutlineColor(_outlineColor);
}

void Button::setOutlineThickness(float thickness)
{
	_outlineThickness = thickness;
	_innerButton.setOutlineThickness(_outlineThickness);
}

void Button::setTextColor(sf::Color color)
{
	_text.setFillColor(color);
}

void Button::setFont(const sf::Font& font)
{
	_text.setFont(font);
}

void Button::setHoverColor(sf::Color color)
{
	_hoverColor = color;
}

void Button::setCornerRadius(float radius)
{
	_innerButton.setCornerRadius(radius);
}

void Button::update(const sf::Time& dt)
{
	_innerButton.setFillColor(_fillColor);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_renderWindow);
	if (_innerButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
	{
		_innerButton.setFillColor(_hoverColor);
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_innerButton);
	target.draw(_text);
}

void Button::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (_innerButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			if (_actionToDo)
			{
				_actionToDo();
			}
			else
			{
				SPDLOG_WARN("Button is clicked, but no action set.");
			}
		}
	}
}

void Button::setSoundOnSelect(const sf::SoundBuffer& soundBuffer)
{
	_soundOnSelect.setBuffer(soundBuffer);
}

void Button::setSoundOnHover(const sf::SoundBuffer& soundBuffer)
{
	_soundOnHover.setBuffer(soundBuffer);
}

void Button::refreshTextOrigin()
{
	sf::Vector2f center { _text.getGlobalBounds().width / 2.f, _text.getGlobalBounds().height / 2.f };
	sf::Vector2f localBounds { center.x + _text.getLocalBounds().left, center.y + _text.getLocalBounds().top };
	sf::Vector2f rounded { std::round(localBounds.x), std::round(localBounds.y) };
	_text.setOrigin(rounded);
}

void Button::refreshTextPosition()
{
	_text.setPosition(_innerButton.getPosition().x + _innerButton.getSize().x / 2, _innerButton.getPosition().y + _innerButton.getSize().y / 2);
}

void Button::initializeInnerButton()
{
	_innerButton.setFillColor(_fillColor);
	_innerButton.setOutlineColor(_outlineColor);
	_innerButton.setOutlineThickness(_outlineThickness);
	_innerButton.setPosition(_position);
	_innerButton.setSize(_size);
}

}
