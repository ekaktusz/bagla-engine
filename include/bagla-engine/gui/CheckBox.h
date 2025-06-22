#pragma once

#include "gui/Widget.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
class RenderWindow;
}

namespace bgl
{
class CheckBox : public bgl::Widget
{
public:
	CheckBox(const sf::RenderWindow& renderWindow);
	~CheckBox();

	void update(const sf::Time& dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event) override;

	const bool isChecked() const
	{
		return _checked;
	}

	void setChecked(bool checked)
	{
		_checked = checked;
	}

	void setSize(float s);
	void setPosition(sf::Vector2f position);
	void setUncheckedColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setCheckedColor(sf::Color color);
	void setOutlineThickness(float thickness);

private:
	void drawCheckMark(sf::RenderTarget& target) const;

private:
	const sf::RenderWindow& _renderWindow; // Required for sf::Mouse class

	bool _checked;

	sf::Color _uncheckedColor;
	sf::Color _outlineColor;
	sf::Color _checkedColor;

	float _outlineThickness;

	sf::RectangleShape _checkBoxShape;
};
}