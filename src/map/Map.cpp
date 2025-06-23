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
	_map = std::make_unique<tmx::Map>();
	bool res = _map->load(filePath);

	if (!res)
	{
		return false;
	}

	for (auto& layer : _map->getLayers())
	{
		if (layer->getType() == tmx::Layer::Type::Tile)
		{
			std::unique_ptr<TileLayer> tileLayer = std::make_unique<TileLayer>(*layer, *_map);
			_tileLayers.try_emplace(layer->getName(), std::move(tileLayer));
		}
		else if (layer->getType() == tmx::Layer::Type::Object)
		{
			tmx::ObjectGroup& objectGroup = layer->getLayerAs<tmx::ObjectGroup>();
			std::unique_ptr<ObjectLayer> objectLayer = std::make_unique<ObjectLayer>(objectGroup);
			_objectLayers.try_emplace(layer->getName(), std::move(objectLayer));
		}
	}

	return true;
}

const bgl::TileLayer& Map::getTileLayer(const std::string& name) const
{
	auto found = _tileLayers.find(name);
	if (found == _tileLayers.end())
	{
		SPDLOG_ERROR("Cant find TileLayer with name: " + name);
	}
	return *found->second;
}

const bgl::ObjectLayer& Map::getObjectLayer(const std::string& name) const
{
	auto found = _objectLayers.find(name);
	if (found == _objectLayers.end())
	{
		SPDLOG_ERROR("Cant find ObjectLayer with name: " + name);
	}
	return *found->second;
}

sf::Vector2f Map::getSize() const
{
	SPDLOG_INFO(" tilsize: x: " + std::to_string(_map->getTileSize().x) + " y: " + std::to_string(_map->getTileSize().y));
	SPDLOG_INFO(" tilcount: x: " + std::to_string(_map->getTileCount().x) + " y: " + std::to_string(_map->getTileCount().y));
	return { (float)_map->getTileSize().x * _map->getTileCount().x, (float)_map->getTileSize().y * _map->getTileCount().y };
}

}