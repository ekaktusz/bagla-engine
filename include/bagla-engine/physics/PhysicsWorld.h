#pragma once

#include <box2d/b2_world.h>
#include <memory>
#include "physics/ContactListener.h"

#include <SFML/Graphics/Drawable.hpp>


namespace bgl
{
	class PhysicsWorld : public sf::Drawable
	{
	public:
		static PhysicsWorld& getInstance()
		{
			static PhysicsWorld s_Instance;
			return s_Instance;
		}

		~PhysicsWorld();

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		PhysicsWorld();

		std::unique_ptr<b2World> m_World;
		ContactListener m_ContactListener;
	};
}