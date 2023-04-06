#include "map/ObjectLayer.h"
#include "tmxlite/ObjectGroup.hpp"
#include "physics/RigidBody.h"

namespace bgl
{
	ObjectLayer::ObjectLayer(tmx::ObjectGroup& objectGroup, b2World* world) : m_ObjectGroup(objectGroup), m_World(world)
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
			if (object.getShape() == tmx::Object::Shape::Rectangle && m_World != nullptr)
			{
				std::unique_ptr<RigidBody> tileRigidBody = std::make_unique<RigidBody>(object.getPosition().x, object.getPosition().y, object.getPosition().x + object.getAABB().width, object.getPosition().y + object.getAABB().height, *world, false);
				m_RigidBodies.push_back(std::move(tileRigidBody));
			}
		}
	}

	ObjectLayer::~ObjectLayer()
	{

	}
}
