#pragma once

#include <box2d/b2_body.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_world_callbacks.h>

namespace bgl
{
class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};
}