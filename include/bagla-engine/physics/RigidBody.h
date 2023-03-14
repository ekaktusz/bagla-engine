#pragma once

#include <box2d/b2_body.h.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_fixture.h>

namespace bgl
{
	class RigidBody
	{
	public:
		RigidBody();
		~RigidBody();

	private:
		b2Body m_Body;
		b2Shape m_Shape;
		b2Fixture m_Fixture;

	};
}