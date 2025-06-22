#include "map/TileLayer.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <spdlog/spdlog.h>

namespace bgl
{
TileLayer::Chunk::Chunk(const tmx::TileLayer& layer, std::vector<const tmx::Tileset*> tilesets, const sf::Vector2f& position, const sf::Vector2f& tileCount,
	const sf::Vector2u& tileSize, std::size_t rowSize, TextureResource& tr, const std::map<std::uint32_t, tmx::Tileset::Tile>& animTiles) :
	_animTiles(animTiles)
{
	setPosition(position);
	_layerOpacity = static_cast<sf::Uint8>(layer.getOpacity() / 1.f * 255.f);
	sf::Color vertColour = sf::Color(200, 200, 200, _layerOpacity);
	auto offset = layer.getOffset();
	_layerOffset.x = offset.x;
	_layerOffset.x = offset.y;
	_chunkTileCount.x = tileCount.x;
	_chunkTileCount.y = tileCount.y;
	_mapTileSize = tileSize;
	const auto& tileIDs = layer.getTiles();

	// go through the tiles and create all arrays (for latter manipulation)
	for (const auto& ts : tilesets)
	{
		if (ts->getImagePath().empty())
		{
			SPDLOG_INFO("This example does not support Collection of Images tilesets");
			SPDLOG_INFO("Chunks using " + ts->getName() + " will not be created");
			continue;
		}
		_chunkArrays.emplace_back(std::make_unique<ChunkArray>(*tr.find(ts->getImagePath())->second, *ts));
	}
	std::size_t xPos = static_cast<std::size_t>(position.x / tileSize.x);
	std::size_t yPos = static_cast<std::size_t>(position.y / tileSize.y);
	for (auto y = yPos; y < yPos + tileCount.y; ++y)
	{
		for (auto x = xPos; x < xPos + tileCount.x; ++x)
		{
			auto idx = (y * rowSize + x);
			_chunkTileIDs.emplace_back(tileIDs[idx]);
			_chunkColors.emplace_back(vertColour);
		}
	}
	generateTiles(true);
}

void TileLayer::Chunk::generateTiles(bool registerAnimation)
{
	if (registerAnimation)
	{
		_activeAnimations.clear();
	}
	for (const auto& ca : _chunkArrays)
	{
		sf::Uint32 idx = 0;
		std::size_t xPos = static_cast<std::size_t>(getPosition().x / _mapTileSize.x);
		std::size_t yPos = static_cast<std::size_t>(getPosition().y / _mapTileSize.y);
		for (auto y = yPos; y < yPos + _chunkTileCount.y; ++y)
		{
			for (auto x = xPos; x < xPos + _chunkTileCount.x; ++x)
			{
				if (idx < _chunkTileIDs.size() && _chunkTileIDs[idx].ID >= ca->firstGID && _chunkTileIDs[idx].ID <= ca->lastGID)
				{
					if (registerAnimation && _animTiles.find(_chunkTileIDs[idx].ID) != _animTiles.end())
					{
						AnimationState as;
						as.animTile = _animTiles[_chunkTileIDs[idx].ID];
						as.startTime = sf::milliseconds(0);
						as.tileCords = sf::Vector2u(x, y);
						_activeAnimations.push_back(as);
					}

					sf::Vector2f tileOffset(x * _mapTileSize.x, (float)y * _mapTileSize.y + _mapTileSize.y - ca->tileSetSize.y);

					auto idIndex = _chunkTileIDs[idx].ID - ca->firstGID;
					sf::Vector2f tileIndex(idIndex % ca->tileCount.x, idIndex / ca->tileCount.x);
					tileIndex.x *= ca->tileSetSize.x;
					tileIndex.y *= ca->tileSetSize.y;
					Tile tile = {
#ifndef __ANDROID__
						sf::Vertex(tileOffset - getPosition(), _chunkColors[idx], tileIndex),
						sf::Vertex(
							tileOffset - getPosition() + sf::Vector2f(ca->tileSetSize.x, 0.f), _chunkColors[idx], tileIndex + sf::Vector2f(ca->tileSetSize.x, 0.f)),
						sf::Vertex(tileOffset - getPosition() + sf::Vector2f(ca->tileSetSize.x, ca->tileSetSize.y),
							_chunkColors[idx],
							tileIndex + sf::Vector2f(ca->tileSetSize.x, ca->tileSetSize.y)),
						sf::Vertex(tileOffset - getPosition() + sf::Vector2f(0.f, ca->tileSetSize.y), _chunkColors[idx], tileIndex + sf::Vector2f(0.f, ca->tileSetSize.y))
#endif
#ifdef __ANDROID__
							sf::Vertex(tileOffset - getPosition(), _chunkColors[idx], tileIndex),
						sf::Vertex(
							tileOffset - getPosition() + sf::Vector2f(ca->tileSetSize.x, 0.f), _chunkColors[idx], tileIndex + sf::Vector2f(ca->tileSetSize.x, 0.f)),
						sf::Vertex(tileOffset - getPosition() + sf::Vector2f(ca->tileSetSize.x, ca->tileSetSize.y),
							_chunkColors[idx],
							tileIndex + sf::Vector2f(ca->tileSetSize.x, ca->tileSetSize.y)),
						sf::Vertex(tileOffset - getPosition(), _chunkColors[idx], tileIndex),
						sf::Vertex(
							tileOffset - getPosition() + sf::Vector2f(0.f, ca->tileSetSize.y), _chunkColors[idx], tileIndex + sf::Vector2f(0.f, ca->tileSetSize.y)),
						sf::Vertex(tileOffset - getPosition() + sf::Vector2f(ca->tileSetSize.x, ca->tileSetSize.y),
							_chunkColors[idx],
							tileIndex + sf::Vector2f(ca->tileSetSize.x, ca->tileSetSize.y))
#endif
					};
					doFlips(_chunkTileIDs[idx].flipFlags, &tile[0].texCoords, &tile[1].texCoords, &tile[2].texCoords, &tile[3].texCoords);
					ca->addTile(tile);
				}
				idx++;
			}
		}
	}
}

std::vector<TileLayer::AnimationState>& TileLayer::Chunk::getActiveAnimations()
{
	return _activeAnimations;
}

tmx::TileLayer::Tile TileLayer::Chunk::getTile(int x, int y) const
{
	return _chunkTileIDs[calcIndexFrom(x, y)];
}

void TileLayer::Chunk::setTile(int x, int y, tmx::TileLayer::Tile tile, bool refresh)
{
	_chunkTileIDs[calcIndexFrom(x, y)] = tile;
	maybeRegenerate(refresh);
}

sf::Color TileLayer::Chunk::getColor(int x, int y) const
{
	return _chunkColors[calcIndexFrom(x, y)];
}

void TileLayer::Chunk::setColor(int x, int y, sf::Color color, bool refresh)
{
	_chunkColors[calcIndexFrom(x, y)] = color;
	maybeRegenerate(refresh);
}

void TileLayer::Chunk::maybeRegenerate(bool refresh)
{
	if (refresh)
	{
		for (const auto& ca : _chunkArrays)
		{
			ca->reset();
		}
		generateTiles();
	}
}

int TileLayer::Chunk::calcIndexFrom(int x, int y) const
{
	return x + y * _chunkTileCount.x;
}

bool TileLayer::Chunk::empty() const
{
	return _chunkArrays.empty();
}

void TileLayer::Chunk::flipY(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3)
{
	// Flip Y
	sf::Vector2f tmp = *v0;
	v0->y = v2->y;
	v1->y = v2->y;
	v2->y = tmp.y;
	v3->y = v2->y;
}

void TileLayer::Chunk::flipX(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3)
{
	// Flip X
	sf::Vector2f tmp = *v0;
	v0->x = v1->x;
	v1->x = tmp.x;
	v2->x = v3->x;
	v3->x = v0->x;
}

void TileLayer::Chunk::flipD(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3)
{
	// Diagonal flip
	sf::Vector2f tmp = *v1;
	v1->x = v3->x;
	v1->y = v3->y;
	v3->x = tmp.x;
	v3->y = tmp.y;
}

void TileLayer::Chunk::doFlips(std::uint8_t bits, sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3)
{
	// 0000 = no change
	// 0100 = vertical = swap y axis
	// 1000 = horizontal = swap x axis
	// 1100 = horiz + vert = swap both axes = horiz+vert = rotate 180 degrees
	// 0010 = diag = rotate 90 degrees right and swap x axis
	// 0110 = diag+vert = rotate 270 degrees right
	// 1010 = horiz+diag = rotate 90 degrees right
	// 1110 = horiz+vert+diag = rotate 90 degrees right and swap y axis
	if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) && !(bits & tmx::TileLayer::FlipFlag::Vertical) && !(bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// Shortcircuit tests for nothing to do
		return;
	}
	else if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) && (bits & tmx::TileLayer::FlipFlag::Vertical) && !(bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// 0100
		flipY(v0, v1, v2, v3);
	}
	else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) && !(bits & tmx::TileLayer::FlipFlag::Vertical) && !(bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// 1000
		flipX(v0, v1, v2, v3);
	}
	else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) && (bits & tmx::TileLayer::FlipFlag::Vertical) && !(bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// 1100
		flipY(v0, v1, v2, v3);
		flipX(v0, v1, v2, v3);
	}
	else if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) && !(bits & tmx::TileLayer::FlipFlag::Vertical) && (bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// 0010
		flipD(v0, v1, v2, v3);
	}
	else if (!(bits & tmx::TileLayer::FlipFlag::Horizontal) && (bits & tmx::TileLayer::FlipFlag::Vertical) && (bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// 0110
		flipX(v0, v1, v2, v3);
		flipD(v0, v1, v2, v3);
	}
	else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) && !(bits & tmx::TileLayer::FlipFlag::Vertical) && (bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// 1010
		flipY(v0, v1, v2, v3);
		flipD(v0, v1, v2, v3);
	}
	else if ((bits & tmx::TileLayer::FlipFlag::Horizontal) && (bits & tmx::TileLayer::FlipFlag::Vertical) && (bits & tmx::TileLayer::FlipFlag::Diagonal))
	{
		// 1110
		flipY(v0, v1, v2, v3);
		flipX(v0, v1, v2, v3);
		flipD(v0, v1, v2, v3);
	}
}

void TileLayer::Chunk::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (const auto& a : _chunkArrays)
	{
		rt.draw(*a, states);
	}
}

void TileLayer::Chunk::ChunkArray::reset()
{
	_Vertices.clear();
}

void TileLayer::Chunk::ChunkArray::addTile(const Chunk::Tile& tile)
{
	for (const auto& v : tile)
	{
		_Vertices.push_back(v);
	}
}

sf::Vector2u TileLayer::Chunk::ChunkArray::getTextureSize() const
{
	return _texture.getSize();
}

TileLayer::Chunk::ChunkArray::ChunkArray(const sf::Texture& t, const tmx::Tileset& ts) : _texture(t)
{
	auto texSize = getTextureSize();
	tileSetSize = ts.getTileSize();
	tileCount.x = texSize.x / tileSetSize.x;
	tileCount.y = texSize.y / tileSetSize.y;
	firstGID = ts.getFirstGID();
	lastGID = ts.getLastGID();
}
}