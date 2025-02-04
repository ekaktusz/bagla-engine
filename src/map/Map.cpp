#include "map/Map.h"
#include <spdlog/spdlog.h>
#include <tmxlite/Layer.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>

namespace bgl
{
Map::Map() {}

Map::~Map() {}

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
			tmx::ObjectGroup& objectGroup = layer->getLayerAs<tmx::ObjectGroup>();
			std::unique_ptr<ObjectLayer> objectLayer = std::make_unique<ObjectLayer>(objectGroup);
			m_ObjectLayers.try_emplace(layer->getName(), std::move(objectLayer));
		}
	}

	return true;
}

const bgl::TileLayer& Map::getTileLayer(const std::string& name) const
{
	auto found = m_TileLayers.find(name);
	if (found == m_TileLayers.end())
	{
		SPDLOG_ERROR("Cant find TileLayer with name: " + name);
	}
	return *found->second;
}

const bgl::ObjectLayer& Map::getObjectLayer(const std::string& name) const
{
	auto found = m_ObjectLayers.find(name);
	if (found == m_ObjectLayers.end())
	{
		SPDLOG_ERROR("Cant find ObjectLayer with name: " + name);
	}
	return *found->second;
}

sf::Vector2f Map::getSize() const
{
	SPDLOG_INFO(" tilsize: x: " + std::to_string(m_Map->getTileSize().x) + " y: " + std::to_string(m_Map->getTileSize().y));
	SPDLOG_INFO(" tilcount: x: " + std::to_string(m_Map->getTileCount().x) + " y: " + std::to_string(m_Map->getTileCount().y));
	return { (float)m_Map->getTileSize().x * m_Map->getTileCount().x, (float)m_Map->getTileSize().y * m_Map->getTileCount().y };
}

}