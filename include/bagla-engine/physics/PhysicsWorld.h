#pragma once

#include <box2d/b2_world.h>
#include <memory>
#include "physics/ContactListener.h"

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

		void update();

	private:
		PhysicsWorld();

		std::unique_ptr<b2World> m_World;
		ContactListener m_ContactListener;
	};
}