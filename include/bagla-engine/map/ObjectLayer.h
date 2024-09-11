#pragma once

#include "physics/RigidBody.h"
#include "tmxlite/Object.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <vector>

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
	tmx::ObjectGroup& m_ObjectGroup;
	// i wonder if i'll ever need this.
	std::vector<RigidBody*> m_RigidBodies;
};
}