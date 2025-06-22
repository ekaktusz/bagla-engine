#pragma once

#include "graphics/RoundedRectangleShape.h"
#include "gui/Widget.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>
#include <string>

namespace bgl
{
class Button : public Widget
{
public:
	Button(const sf::RenderWindow& renderWindow);
	Button(const sf::RenderWindow& renderWindow, const std::string& buttonString, sf::Vector2f position, sf::Vector2f size, std::function<void()> actionToDo);

	sf::Vector2f getSize()
	{
		return _size;
	}

	sf::Vector2f getPosition()
	{
		return _position;
	}

	void setString(const std::string& buttonString);
	void setActionTodo(std::function<void()> actionToDo);

	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(float thickness);
	void setTextColor(sf::Color color);
	void setFont(const sf::Font& font);
	void setHoverColor(sf::Color color);
	void setCornerRadius(float radius);

	void update(const sf::Time& dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event) override;

	void setSoundOnSelect(const sf::SoundBuffer& soundBuffer);
	void setSoundOnHover(const sf::SoundBuffer& soundBuffer);

private:
	void refreshTextOrigin();
	void refreshTextPosition();
	void initializeInnerButton();

private:
	const sf::RenderWindow& _renderWindow; // Required for sf::Mouse class

	sf::Text _text;
	sf::Vector2f _position;
	sf::Vector2f _size;

	std::function<void()> _actionToDo;

	sf::Color _fillColor;
	sf::Color _outlineColor;
	sf::Color _textColor;
	sf::Color _hoverColor;

	float _outlineThickness;

	bgl::RoundedRectangleShape _innerButton;

	sf::Sound _soundOnSelect;
	sf::Sound _soundOnHover;
};

}
