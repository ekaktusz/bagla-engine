#pragma once

#include "gui/Widget.h"
#include <string>
#include <SFML/Graphics/Text.hpp>

#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include "graphics/RoundedRectangleShape.h"


namespace bgl
{
	class Button : public Widget
	{
	public:
		Button(const sf::RenderWindow& renderWindow);
		Button(const sf::RenderWindow& renderWindow, const std::string& buttonString, sf::Vector2f position, sf::Vector2f size, std::function<void()> actionToDo);

		sf::Vector2f getSize() { return m_Size; }
		sf::Vector2f getPosition() { return m_Position; }

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
		const sf::RenderWindow& m_RenderWindow; // Required for sf::Mouse class

		sf::Text m_Text;
		sf::Vector2f m_Position;
		sf::Vector2f m_Size;

		std::function<void()> m_ActionToDo;

		sf::Color m_FillColor;
		sf::Color m_OutlineColor;
		sf::Color m_TextColor;
		sf::Color m_HoverColor;

		float m_OutlineThickness;

		bgl::RoundedRectangleShape m_InnerButton;

		sf::Sound m_SoundOnSelect;
		sf::Sound m_SoundOnHover;


	};

}
