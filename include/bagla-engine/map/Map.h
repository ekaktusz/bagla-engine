#pragma once

#include <unordered_map>
#include <memory>

#include "map/TileLayer.h"
#include "map/ObjectLayer.h"

namespace bgl
{
	class Map
	{
	public:
		Map();
		~Map();

		bool loadFromFile(const std::string& filePath, b2World* world = nullptr);

		const TileLayer& getTileLayer(const std::string& name);
		const ObjectLayer& getObjectLayer(const std::string& name);
		//TileLayer getTileLayer(unsigned int idx);
		//ObjectLayer getObjectLayer(unsigned int idx);

	private:
		std::unique_ptr<tmx::Map> m_Map;

		std::unordered_map<std::string, std::unique_ptr<TileLayer>> m_TileLayers;
		std::unordered_map<std::string, std::unique_ptr<ObjectLayer>> m_ObjectLayers;
	};
}