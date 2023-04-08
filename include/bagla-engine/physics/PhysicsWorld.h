#pragma once

#include <box2d/b2_world.h>

namespace bgl
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld() = default;
		~PhysicsWorld();

		void update();

	private:
		std::unique_ptr<b2World> m_World;
		ContactListener m_ContactListener;
	};
}