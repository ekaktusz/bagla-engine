#include "map/ObjectLayer.h"
#include "tmxlite/ObjectGroup.hpp"

namespace bgl
{
	ObjectLayer::ObjectLayer(tmx::ObjectGroup& objectGroup) : m_ObjectGroup(objectGroup)
	{
		const auto& properties = objectGroup.getProperties();
		for (const auto& prop : properties)
		{
			if (prop.getName() == "solid" && prop.getType() == tmx::Property::Type::Boolean && prop.getBoolValue())
			{
				
			}
		}
	}

	ObjectLayer::~ObjectLayer()
	{

	}
}
