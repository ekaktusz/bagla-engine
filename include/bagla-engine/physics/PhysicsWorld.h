#pragma once

#include "GameObject.h"
#include "physics/ContactListener.h"
#include "physics/DebugDraw.h"

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include <box2d/b2_world.h>

namespace sf
{
class Time;
}

namespace bgl
{
class RigidBody;

class PhysicsWorld : public GameObject, public sf::Drawable
{
public:
	friend class RigidBody;

	static PhysicsWorld& getInstance()
	{
		static PhysicsWorld instance;
		return instance;
	}

	void cleanUp();

	void update(const sf::Time& dt) override;
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

private:
	PhysicsWorld();

private:
	std::unique_ptr<b2World> _world;

	ContactListener _contactListener;
	std::unique_ptr<DebugDraw> _debugDraw;

	std::vector<bgl::RigidBody*> _bodiesToDestroy;
};
}
