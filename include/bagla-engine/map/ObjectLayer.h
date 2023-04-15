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
		ObjectLayer(tmx::ObjectGroup& objectGroup);
		~ObjectLayer();
	private:
		tmx::ObjectGroup& m_ObjectGroup;
		
		std::vector<std::unique_ptr<RigidBody>> m_RigidBodies;
	};
}