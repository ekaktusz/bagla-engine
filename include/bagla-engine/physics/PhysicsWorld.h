#pragma once

#include <box2d/b2_world.h>
#include <memory>
#include "physics/ContactListener.h"

#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
	class Time;
}

namespace bgl
{
	class PhysicsWorld
	{
	public:
		static PhysicsWorld& getInstance()
		{
			static PhysicsWorld s_Instance;
			return s_Instance;
		}

		~PhysicsWorld();

		void update(const sf::Time& dt);

	public:
		std::unique_ptr<b2World> m_World;

	private:
		PhysicsWorld();

	private:
		ContactListener m_ContactListener;
	};
}