#include "map/ObjectLayer.h"
#include "physics/PhysicsWorld.h"
#include "tmxlite/ObjectGroup.hpp"
#include <physics/RigidBody.h>
#include <spdlog/spdlog.h>

namespace bgl
{
ObjectLayer::ObjectLayer(tmx::ObjectGroup& objectGroup) : m_ObjectGroup(objectGroup)
{
	if (isSolidFlagPresent())
	{
		initializeRigidBodies();
	}
}

bool ObjectLayer::isSolidFlagPresent() const
{
	const auto& properties = m_ObjectGroup.getProperties();
	for (const auto& prop : properties)
	{
		if (prop.getName() == "solid" && prop.getType() == tmx::Property::Type::Boolean && prop.getBoolValue())
		{
			return true;
		}
	}
	return false;
}

void ObjectLayer::initializeRigidBodies()
{
	const auto& objects = m_ObjectGroup.getObjects();
	for (const auto& object : objects)
	{
		//TODO: more shapes
		if (object.getShape() == tmx::Object::Shape::Rectangle)
		{
			RigidBody* tileRigidBody =
				PhysicsWorld::getInstance().newRigidBody(object.getPosition().x, object.getPosition().y, object.getAABB().width, object.getAABB().height, false);
			tileRigidBody->setUserCustomData(std::string("solid"));
			SPDLOG_INFO("x: " + std::to_string(object.getPosition().x) + " y:" + std::to_string(object.getPosition().y) + " w:" + std::to_string(object.getAABB().width)
				+ " h:" + std::to_string(object.getAABB().height));
			m_RigidBodies.push_back(tileRigidBody);
		}
	}
}

const std::vector<tmx::Object>& ObjectLayer::getObjects() const
{
	return m_ObjectGroup.getObjects();
}

const tmx::Object& ObjectLayer::getFirstObject() const
{
	return m_ObjectGroup.getObjects().front();
}

ObjectLayer::~ObjectLayer()
{
	for (RigidBody* rigidBody : m_RigidBodies)
	{
		PhysicsWorld::getInstance().destroyRigidBody(rigidBody);
	}
}

}
