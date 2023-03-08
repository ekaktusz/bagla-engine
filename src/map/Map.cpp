#include "map/Map.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>

namespace bgl
{
	Map::Map()
	{

	}

	Map::~Map()
	{

	}

	bool Map::loadFromFile(const std::string& filePath)
	{
		bool res = m_Map->load(filePath);
		
		if (!res)
		{
			return false;
		}
		
		for (const auto& layer : m_Map->getLayers())
		{
			if (layer->getType() == tmx::Layer::Type::Tile)
			{
				std::unique_ptr<TileLayer> tileLayer = std::make_unique<TileLayer>(*layer, *m_Map);
				m_TileLayers.try_emplace(layer->getName(), std::move(tileLayer));
			}
			else if (layer->getType() == tmx::Layer::Type::Object)
			{

			}
		}

		return true;
	}
}