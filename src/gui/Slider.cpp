#include "gui/Slider.h"

#include "MathExtensions.h"
#include "gui/FocusLock.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <spdlog/spdlog.h>

namespace bgl
{
Slider::Slider(const sf::RenderWindow& renderWindow) : _renderWindow(renderWindow), _Progress(0.5)
{
	_outerSlider.setFillColor(sf::Color::Black);
	_outerSlider.setOutlineColor(sf::Color::White);
	_outerSlider.setOutlineThickness(1);

	_innerSlider.setFillColor(sf::Color::White);
	_indicator.setFillColor(sf::Color::Red);

	_text.setString("");
	_text.setFillColor(sf::Color::White);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(1);
}

void Slider::update(const sf::Time& dt)
{
	_indicator.setPosition(_outerSlider.getPosition().x + _Progress * (_outerSlider.getSize().x - _indicator.getSize().x), _outerSlider.getPosition().y);
	_innerSlider.setSize({ (_outerSlider.getSize().x - 4) * _Progress, _innerSlider.getSize().y });

	updateTextPosition();

	const sf::Vector2i mousePosition = sf::Mouse::getPosition(_renderWindow);
	// if (_outerSlider.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
	// {
	// 	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	// 	{
	// 		if (!FocusLock::isLocked())
	// 		{
	// 			FocusLock::lockFocus(this);
	// 		}
	// 	}
	// }

	if (FocusLock::isWidgetInFocus(this))
	{
		_Progress = mid(0.f, (mousePosition.x - _outerSlider.getPosition().x) / _outerSlider.getSize().x, 1.f);
		if (_onProgressChange)
		{
			_onProgressChange(_Progress);
		}
	}
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_outerSlider);
	target.draw(_innerSlider);
	target.draw(_indicator);
	if (_text.getString() != "")
	{
		target.draw(_text);
	}
}

void Slider::handleEvent(const sf::Event& event)
{
	const sf::Vector2i mousePosition = sf::Mouse::getPosition(_renderWindow);

	if (event.type == sf::Event::MouseButtonPressed && !FocusLock::isWidgetInFocus(this))
	{
		if (_outerSlider.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			FocusLock::lockFocus(this);
		}
	}

	if (event.type == sf::Event::MouseButtonReleased && FocusLock::isWidgetInFocus(this))
	{
		FocusLock::unlockFocus();
	}
}

float Slider::getProgress() const
{
	return _Progress;
}

void Slider::setProgress(float progress)
{
	if (progress > 1 || progress < 0)
	{
		SPDLOG_WARN("not valid progress: " + std::to_string(progress));
		return;
	}
	_Progress = progress;
	if (_onProgressChange)
	{
		_onProgressChange(_Progress);
	}
}

sf::Vector2f Slider::getSize() const
{
	return _outerSlider.getSize();
}

void Slider::setSize(sf::Vector2f size)
{
	_outerSlider.setSize(size);
	_innerSlider.setSize(size - sf::Vector2f(4, 4));
	_indicator.setSize({ 5, size.y });

	_text.setCharacterSize(_innerSlider.getSize().y);
}

sf::Vector2f Slider::getPosition() const
{
	return _outerSlider.getPosition();
}

void Slider::setPosition(sf::Vector2f position)
{
	_outerSlider.setPosition(position);
	_innerSlider.setPosition(position + sf::Vector2f(2, 2));
}

void Slider::updateTextPosition()
{
	sf::Vector2f center { _text.getGlobalBounds().width / 2.f, _text.getGlobalBounds().height / 2.f };
	sf::Vector2f localBounds { center.x + _text.getLocalBounds().left, center.y + _text.getLocalBounds().top };
	sf::Vector2f rounded { std::round(localBounds.x), std::round(localBounds.y) };
	_text.setOrigin(rounded);
	_text.setPosition(_outerSlider.getPosition().x + _outerSlider.getSize().x / 2, _innerSlider.getPosition().y + _innerSlider.getSize().y / 2);
}

void Slider::setFont(const sf::Font& font)
{
	_text.setFont(font);
}

void Slider::setString(const std::string& str)
{
	_text.setString(str);
}

}
