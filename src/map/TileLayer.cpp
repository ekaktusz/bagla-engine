#include "map/TileLayer.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <spdlog/spdlog.h>
#include <tmxlite/Map.hpp>

namespace bgl
{
TileLayer::TileLayer(const tmx::Layer& tileLayer, const tmx::Map& map)
{
	// round the chunk size to the nearest tile
	const auto tileSize = map.getTileSize();
	_chunkSize.x = std::floor(_chunkSize.x / tileSize.x) * tileSize.x;
	_chunkSize.y = std::floor(_chunkSize.y / tileSize.y) * tileSize.y;
	_mapTileSize.x = map.getTileSize().x;
	_mapTileSize.y = map.getTileSize().y;
	createChunks(map, tileLayer.getLayerAs<tmx::TileLayer>());

	auto mapSize = map.getBounds();
	_GlobalBounds.width = mapSize.width;
	_GlobalBounds.height = mapSize.height;
}

TileLayer::~TileLayer() {}

const sf::FloatRect& TileLayer::getGlobalBounds() const
{
	return _GlobalBounds;
}

void TileLayer::setTile(int tileX, int tileY, tmx::TileLayer::Tile tile, bool refresh)
{
	sf::Vector2u chunkLocale;
	const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
	selectedChunk->setTile(chunkLocale.x, chunkLocale.y, tile, refresh);
}

tmx::TileLayer::Tile TileLayer::getTile(int tileX, int tileY)
{
	sf::Vector2u chunkLocale;
	const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
	return selectedChunk->getTile(chunkLocale.x, chunkLocale.y);
}

void TileLayer::setColor(int tileX, int tileY, sf::Color color, bool refresh)
{
	sf::Vector2u chunkLocale;
	const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
	selectedChunk->setColor(chunkLocale.x, chunkLocale.y, color, refresh);
}

sf::Color TileLayer::getColor(int tileX, int tileY)
{
	sf::Vector2u chunkLocale;
	const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
	return selectedChunk->getColor(chunkLocale.x, chunkLocale.y);
}

void TileLayer::update(sf::Time elapsed)
{
	for (auto& c : _visibleChunks)
	{
		for (AnimationState& as : c->getActiveAnimations())
		{
			as.currentTime += elapsed;

			tmx::TileLayer::Tile tile;
			tile.ID = as.animTile.animation.frames[0].tileID;
			tile.flipFlags = 0; // TODO: get flipFlags from original tmx::TileLayer::Tile

			std::uint32_t animTime = 0;
			for (const auto& frame : as.animTile.animation.frames)
			{
				animTime += frame.duration;
				if (as.currentTime.asMilliseconds() >= animTime)
				{
					tile.ID = frame.tileID;
					if (frame == as.animTile.animation.frames.back())
					{
						as.currentTime = sf::milliseconds(0);
					}
				}
			}

			setTile(as.tileCords.x, as.tileCords.y, tile);
		}
	}
}

void TileLayer::createChunks(const tmx::Map& map, const tmx::TileLayer& layer)
{
	// look up all the tile sets and load the textures
	const auto& tileSets = map.getTilesets();
	const auto& layerIDs = layer.getTiles();
	std::uint32_t maxID = std::numeric_limits<std::uint32_t>::max();
	std::vector<const tmx::Tileset*> usedTileSets;

	for (auto i = tileSets.rbegin(); i != tileSets.rend(); ++i)
	{
		for (const auto& tile : layerIDs)
		{
			if (tile.ID >= i->getFirstGID() && tile.ID < maxID)
			{
				usedTileSets.push_back(&(*i));
				break;
			}
		}
		maxID = i->getFirstGID();
	}

	sf::Image fallback;
	fallback.create(2, 2, sf::Color::Magenta);
	for (const auto& ts : usedTileSets)
	{
		const auto& path = ts->getImagePath();
		// std::unique_ptr<sf::Texture> newTexture = std::make_unique<sf::Texture>();
		std::unique_ptr<sf::Texture> newTexture = std::make_unique<sf::Texture>();
		sf::Image img;
		if (!img.loadFromFile(path))
		{
			newTexture->loadFromImage(fallback);
		}
		else
		{
			if (ts->hasTransparency())
			{
				auto transparency = ts->getTransparencyColour();
				img.createMaskFromColor({ transparency.r, transparency.g, transparency.b, transparency.a });
			}
			newTexture->loadFromImage(img);
		}
		_textureResource.insert(std::make_pair(path, std::move(newTexture)));
	}

	// calculate the number of chunks in the layer
	// and create each one
	const auto bounds = map.getBounds();
	_chunkCount.x = static_cast<sf::Uint32>(std::ceil(bounds.width / _chunkSize.x));
	_chunkCount.y = static_cast<sf::Uint32>(std::ceil(bounds.height / _chunkSize.y));

	sf::Vector2u tileSize(map.getTileSize().x, map.getTileSize().y);

	for (auto y = 0u; y < _chunkCount.y; ++y)
	{
		sf::Vector2f tileCount(_chunkSize.x / tileSize.x, _chunkSize.y / tileSize.y);
		for (auto x = 0u; x < _chunkCount.x; ++x)
		{
			// calculate size of each Chunk (clip against map)
			if ((x + 1) * _chunkSize.x > bounds.width)
			{
				tileCount.x = (bounds.width - x * _chunkSize.x) / map.getTileSize().x;
			}
			if ((y + 1) * _chunkSize.y > bounds.height)
			{
				tileCount.y = (bounds.height - y * _chunkSize.y) / map.getTileSize().y;
			}
			// _chunks.emplace_back(std::make_unique<Chunk>(layer, usedTileSets,
			//     sf::Vector2f(x * _chunkSize.x, y * _chunkSize.y), tileCount, map.getTileCount().x,
			//     _textureResource));
			_chunks.emplace_back(std::make_unique<Chunk>(layer,
				usedTileSets,
				sf::Vector2f(x * _chunkSize.x, y * _chunkSize.y),
				tileCount,
				tileSize,
				map.getTileCount().x,
				_textureResource,
				map.getAnimatedTiles()));
		}
	}
}

void TileLayer::updateVisibility(const sf::View& view) const
{
	sf::Vector2f viewCorner = view.getCenter();
	viewCorner -= view.getSize() / 2.f;

	int posX = static_cast<int>(std::floor(viewCorner.x / _chunkSize.x));
	int posY = static_cast<int>(std::floor(viewCorner.y / _chunkSize.y));
	int posX2 = static_cast<int>(std::ceil((viewCorner.x + view.getSize().x) / _chunkSize.x));
	int posY2 = static_cast<int>(std::ceil((viewCorner.y + view.getSize().x) / _chunkSize.y));

	std::vector<Chunk*> visible;
	for (auto y = posY; y < posY2; ++y)
	{
		for (auto x = posX; x < posX2; ++x)
		{
			std::size_t idx = y * int(_chunkCount.x) + x;
			if (idx >= 0u && idx < _chunks.size() && !_chunks[idx]->empty())
			{
				visible.push_back(_chunks[idx].get());
			}
		}
	}

	std::swap(_visibleChunks, visible);
}

void TileLayer::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	// calc view coverage and draw nearest chunks
	updateVisibility(rt.getView());
	for (const auto& c : _visibleChunks)
	{
		rt.draw(*c, states);
	}
}

}