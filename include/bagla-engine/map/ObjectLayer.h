#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include "physics/RigidBody.h"

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
	};
}