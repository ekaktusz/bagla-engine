#include "map/Map.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <spdlog/spdlog.h>
#include <tmxlite/ObjectGroup.hpp>

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
		m_Map = std::make_unique<tmx::Map>();
		bool res = m_Map->load(filePath);
		
		if (!res)
		{
			return false;
		}
		
		for (auto& layer : m_Map->getLayers())
		{
			if (layer->getType() == tmx::Layer::Type::Tile)
			{
				std::unique_ptr<TileLayer> tileLayer = std::make_unique<TileLayer>(*layer, *m_Map);
				m_TileLayers.try_emplace(layer->getName(), std::move(tileLayer));
			}
			else if (layer->getType() == tmx::Layer::Type::Object)
			{
				std::unique_ptr<ObjectLayer> objectLayer = std::make_unique<ObjectLayer>(layer->getLayerAs<tmx::ObjectGroup>());
				m_ObjectLayers.try_emplace(layer->getName(), std::move(objectLayer));
			}
		}

		return true;
	}

	const bgl::TileLayer& Map::getTileLayer(const std::string& name)
	{
		auto found = m_TileLayers.find(name);
		if (found == m_TileLayers.end())
		{
			spdlog::error("Cant find tilelayer with name: " + name);
		}
		return *found->second;
	}

}