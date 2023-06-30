#include "map/ObjectLayer.h"
#include "tmxlite/ObjectGroup.hpp"
#include "physics/PhysicsWorld.h"
#include <spdlog/spdlog.h>

namespace bgl
{
	ObjectLayer::ObjectLayer(tmx::ObjectGroup& objectGroup) : m_ObjectGroup(objectGroup)
	{
		const auto& properties = objectGroup.getProperties();
		bool isSolid = false;
		for (const auto& prop : properties)
		{
			if (prop.getName() == "solid" && prop.getType() == tmx::Property::Type::Boolean && prop.getBoolValue())
			{
				isSolid = true;
				break;
			}
		}

		const auto& objects = objectGroup.getObjects();
		for (const auto& object : objects)
		{
			if (object.getShape() == tmx::Object::Shape::Rectangle && isSolid)
			{
				RigidBody* tileRigidBody = PhysicsWorld::getInstance().newRigidBody(object.getPosition().x, object.getPosition().y, object.getAABB().width, object.getAABB().height, false);
				spdlog::info("x: " + std::to_string(object.getPosition().x) + " y:" + std::to_string(object.getPosition().y) + " w:" + std::to_string(object.getAABB().width) + " h:" + std::to_string(object.getAABB().height));
				m_RigidBodies.push_back(tileRigidBody);
			}
		}
	}

	ObjectLayer::~ObjectLayer()
	{

	}
}
