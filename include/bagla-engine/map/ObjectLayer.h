#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>


namespace bgl
{
	class ObjectLayer
	{
	public:
		ObjectLayer();
		~ObjectLayer();
	private:;
		std::vector<sf::FloatRect> m_ObjectBounds;
	};
}