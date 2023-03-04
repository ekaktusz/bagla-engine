#pragma once

#include "Widget.h"

namespace bgl
{
	class Label : public Widget
	{
	public:
		void update(const sf::Time& dt);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void handleEvent(const sf::Event& event);

	private:
		sf::Text m_Text;
	};
}