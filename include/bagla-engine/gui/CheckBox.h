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
		return m_Checked;
	}

	void setChecked(bool checked)
	{
		m_Checked = checked;
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
	const sf::RenderWindow& m_RenderWindow; // Required for sf::Mouse class

	bool m_Checked;

	sf::Color m_UncheckedColor;
	sf::Color m_OutlineColor;
	sf::Color m_CheckedColor;

	float m_OutlineThickness;

	sf::RectangleShape m_CheckBoxShape;
};
}