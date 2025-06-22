#pragma once

#include "map/ObjectLayer.h"
#include "map/TileLayer.h"

#include <memory>
#include <unordered_map>

namespace bgl
{
class Map
{
public:
	Map();
	~Map();

	bool loadFromFile(const std::string& filePath);

	const TileLayer& getTileLayer(const std::string& name) const;
	const ObjectLayer& getObjectLayer(const std::string& name) const;
	//TileLayer getTileLayer(unsigned int idx);
	//ObjectLayer getObjectLayer(unsigned int idx);

	sf::Vector2f getSize() const;

private:
	std::unique_ptr<tmx::Map> _map;

	std::unordered_map<std::string, std::unique_ptr<TileLayer>> _tileLayers;
	std::unordered_map<std::string, std::unique_ptr<ObjectLayer>> _objectLayers;
};
}