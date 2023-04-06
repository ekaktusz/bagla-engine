#pragma once

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class b2Body;
class b2World;

namespace bgl
{
	class RigidBody final
	{
	public:
		RigidBody(float x, float y, float sx, float sy, b2World& world, bool dynamic = true, float density = 0.f);
		RigidBody(sf::Vector2f position, sf::Vector2f size, b2World& world, bool dynamic = true, float density = 0.f);
		~RigidBody();

		sf::Vector2f getPosition() const;
		void setPosition(sf::Vector2f position);

		void setLinearVelocity(sf::Vector2f velocity);

	private:
		b2Body* m_Body;
		b2BodyDef m_BodyDef;
		b2PolygonShape m_Shape;
		b2Fixture* m_Fixture;

		b2World& m_World;

		sf::RectangleShape m_RigidBodyRectangleShape;
	};
}