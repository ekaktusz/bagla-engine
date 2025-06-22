#pragma once

#include "gui/Widget.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <functional>
#include <string>

namespace sf
{
class RenderWindow;
};

namespace bgl
{
class Slider : public Widget
{
public:
	Slider(const sf::RenderWindow& renderWindow);

	void update(const sf::Time& dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event) override;

	float getProgress() const;
	void setProgress(float progress);

	sf::Vector2f getSize() const;
	void setSize(sf::Vector2f size);

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);

	void updateTextPosition();

	void setOnProgressChange(std::function<void(float)> onProgressChange)
	{
		_onProgressChange = onProgressChange;
	}

	void setFont(const sf::Font& font);
	void setString(const std::string& str);

private:
	const sf::RenderWindow& _renderWindow;

	float _Progress; // between 0 and 1

	sf::RectangleShape _outerSlider;
	sf::RectangleShape _innerSlider;
	sf::RectangleShape _indicator;

	sf::Text _text;

	std::function<void(float)> _onProgressChange;
};
}