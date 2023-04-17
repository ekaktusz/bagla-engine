#pragma once

#include <box2d/b2_world.h>
#include <memory>
#include "physics/ContactListener.h"

#include <SFML/Graphics/Drawable.hpp>
#include "physics/DebugDraw.h"

namespace sf
{
	class Time;
}

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

		void update(const sf::Time& dt);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void initDebugDraw(sf::RenderWindow& renderWindow);

	public:
		std::unique_ptr<b2World> m_World;

	private:
		PhysicsWorld();

	private:
		ContactListener m_ContactListener;
		std::unique_ptr<DebugDraw> m_DebugDraw;
	};
}