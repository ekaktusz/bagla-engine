#pragma once

#include "physics/RigidBody.h"

#include <SFML/Graphics/Rect.hpp>

#include <memory>
#include <vector>

#include <tmxlite/Object.hpp>

namespace tmx
{
class ObjectGroup;
}

namespace bgl
{
class ObjectLayer
{
public:
	ObjectLayer(tmx::ObjectGroup& objectGroup);
	~ObjectLayer();

	const std::vector<tmx::Object>& getObjects() const;
	const tmx::Object& getFirstObject() const;

private:
	bool isSolidFlagPresent() const;
	void initializeRigidBodies();

private:
	tmx::ObjectGroup& _objectGroup;
	// i wonder if i'll ever need this.
	std::vector<RigidBody*> _rigidBodies;
};
}