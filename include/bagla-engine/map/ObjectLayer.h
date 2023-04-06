#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include "physics/RigidBody.h"
#include <memory>

namespace tmx
{
	class ObjectGroup;
}

namespace bgl
{
	class ObjectLayer
	{
	public:
		ObjectLayer(tmx::ObjectGroup& objectGroup, b2World* world = nullptr);
		~ObjectLayer();
	private:
		tmx::ObjectGroup& m_ObjectGroup;
		b2World* m_World;
		
		std::vector<std::unique_ptr<RigidBody>> m_RigidBodies;
	};
}