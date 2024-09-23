#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <any>
#include <functional>

#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

class b2Body;
class b2World;

namespace bgl
{

class RigidBody final
{
public:
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	sf::Vector2f getSize() const;
	void setSize(float sx, float sy);

	void setLinearVelocity(sf::Vector2f velocity);
	void setLinearVelocity(float vx, float vy);

	void setGravityScale(float gravityScale);

	void setBeginContact(std::function<void(RigidBody*, sf::Vector2f)> beginContact);
	void setEndContact(std::function<void(RigidBody*, sf::Vector2f)> endContact);

	void setSensor(bool sensor);

	void beginContact(RigidBody* other, sf::Vector2f collisionNormal);
	void endContact(RigidBody* other, sf::Vector2f collisionNormal);

	const std::any& getUserCustomData() const;
	void setUserCustomData(const std::any& userCustomData);

private:
	// has to be instantiated through the physicsworld object
	RigidBody(float x, float y, float sx, float sy, bool dynamic = true, float density = 0.f);
	RigidBody(sf::Vector2f position, sf::Vector2f size, bool dynamic = true, float density = 0.f);

	void initialize(float x, float y, float sx, float sy, bool dynamic = true, float density = 0.f);

private:
	friend class PhysicsWorld;

	b2Body* m_Body;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_Shape;
	b2Fixture* m_Fixture;

	sf::RectangleShape m_RigidBodyRectangleShape;

	std::function<void(RigidBody*, sf::Vector2f)> m_BeginContact;
	std::function<void(RigidBody*, sf::Vector2f)> m_EndContact;

	std::any m_UserCustomData;
};

}