#pragma once

#include <box2d/b2_world.h>
#include <memory>
#include "physics/ContactListener.h"

#include <SFML/Graphics/Drawable.hpp>
#include "physics/DebugDraw.h"
#include <vector>

namespace sf
{
	class Time;
}

namespace bgl
{
	class RigidBody;

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

		void destroyRigidBody(bgl::RigidBody* body);
		bgl::RigidBody* newRigidBody(float x, float y, float sx, float sy, bool dynamic = true, float density = 0.f);
		bgl::RigidBody* newRigidBody(sf::Vector2f position, sf::Vector2f size, bool dynamic = true, float density = 0.f);

		static constexpr float PIXEL_PER_METER = 32.f;

		static sf::Vector2f scaleToGraphics(b2Vec2 coordinates);
		static b2Vec2 scaleToPhysics(sf::Vector2f coordinates);
		static float scaleToGraphics(float f);
		static float scaleToPhysics(float f);

	public:
		std::unique_ptr<b2World> m_World;

	private:
		PhysicsWorld();

	private:
		ContactListener m_ContactListener;
		std::unique_ptr<DebugDraw> m_DebugDraw;

		std::vector<bgl::RigidBody*> m_BodiesToDestroy;
	};
}