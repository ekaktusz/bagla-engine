#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Time.hpp>

#include <cmath>
#include <map>
#include <vector>

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>

namespace sf
{
class View;
}

namespace tmx
{
class Layer;
}

namespace bgl
{
class TileLayer final : public sf::Drawable
{
public:
	TileLayer(const TileLayer&) = delete;
	TileLayer(const tmx::Layer& tileLayer, const tmx::Map& map);
	~TileLayer();

	TileLayer& operator=(const TileLayer&) = delete;

	const sf::FloatRect& getGlobalBounds() const;
	tmx::TileLayer::Tile getTile(int tileX, int tileY);
	sf::Color getColor(int tileX, int tileY);

	void setTile(int tileX, int tileY, tmx::TileLayer::Tile tile, bool refresh = true);
	void setColor(int tileX, int tileY, sf::Color color, bool refresh = true);

	void update(sf::Time elapsed);

private:
	void createChunks(const tmx::Map& map, const tmx::TileLayer& layer);
	void updateVisibility(const sf::View& view) const;
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;

private:
	// increasing _chunkSize by 4; fixes render problems when mapsize != chunksize
	// sf::Vector2f _chunkSize = sf::Vector2f(1024.f, 1024.f);
	sf::Vector2f _chunkSize = sf::Vector2f(512.f, 512.f);
	sf::Vector2u _chunkCount;
	sf::Vector2u _mapTileSize; // general Tilesize of Map
	sf::FloatRect _GlobalBounds;

	using TextureResource = std::map<std::string, std::unique_ptr<sf::Texture>>;
	TextureResource _textureResource;

	struct AnimationState
	{
		sf::Vector2u tileCords;
		sf::Time startTime;
		sf::Time currentTime;
		tmx::Tileset::Tile animTile;
		std::uint8_t flipFlags;
	};

	class Chunk final : public sf::Transformable, public sf::Drawable
	{
	public:
		using Ptr = std::unique_ptr<Chunk>;

		// the Android OpenGL driver isn't capable of rendering quads,
		// so we need to use two triangles per tile instead
#ifdef __ANDROID__
		using Tile = std::array<sf::Vertex, 6u>;
#endif
#ifndef __ANDROID__
		using Tile = std::array<sf::Vertex, 4u>;
#endif

		Chunk(const Chunk&) = delete;
		Chunk(const tmx::TileLayer& layer, std::vector<const tmx::Tileset*> tilesets, const sf::Vector2f& position, const sf::Vector2f& tileCount,
			const sf::Vector2u& tileSize, std::size_t rowSize, TextureResource& tr, const std::map<std::uint32_t, tmx::Tileset::Tile>& animTiles);
		~Chunk() = default;

		Chunk& operator=(const Chunk&) = delete;

		void generateTiles(bool registerAnimation = false);

		std::vector<AnimationState>& getActiveAnimations();
		tmx::TileLayer::Tile getTile(int x, int y) const;
		sf::Color getColor(int x, int y) const;

		void setTile(int x, int y, tmx::TileLayer::Tile tile, bool refresh);
		void setColor(int x, int y, sf::Color color, bool refresh);

		void maybeRegenerate(bool refresh);

		int calcIndexFrom(int x, int y) const;
		bool empty() const;

		void flipY(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3);
		void flipX(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3);
		void flipD(sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3);
		void doFlips(std::uint8_t bits, sf::Vector2f* v0, sf::Vector2f* v1, sf::Vector2f* v2, sf::Vector2f* v3);

	private:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;

	private:
		class ChunkArray final : public sf::Drawable
		{
		public:
			explicit ChunkArray(const sf::Texture& t, const tmx::Tileset& ts);

			~ChunkArray() = default;
			ChunkArray(const ChunkArray&) = delete;
			ChunkArray& operator=(const ChunkArray&) = delete;

			void reset();
			void addTile(const Chunk::Tile& tile);
			sf::Vector2u getTextureSize() const;

		public:
			using Ptr = std::unique_ptr<ChunkArray>;
			tmx::Vector2u tileSetSize;
			sf::Vector2u tileCount;
			std::uint32_t firstGID, lastGID;

		private:
			const sf::Texture& _texture;
			std::vector<sf::Vertex> _Vertices;

			void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
			{
				states.texture = &_texture;
#ifndef __ANDROID__
				rt.draw(_Vertices.data(), _Vertices.size(), sf::Quads, states);
#endif
#ifdef __ANDROID__
				rt.draw(_Vertices.data(), _Vertices.size(), sf::Triangles, states);
#endif
			}
		};

		sf::Uint8 _layerOpacity;   // opacity of the layer
		sf::Vector2f _layerOffset; // Layer offset

		sf::Vector2u _mapTileSize;						 // general Tilesize of Map
		sf::Vector2f _chunkTileCount;					 // chunk tilecount
		std::vector<tmx::TileLayer::Tile> _chunkTileIDs; // stores all tiles in this chunk for later manipulation
		std::vector<sf::Color> _chunkColors;			 // stores colors for extended color effects

		std::map<std::uint32_t, tmx::Tileset::Tile> _animTiles; // animation catalogue
		std::vector<AnimationState> _activeAnimations;			// Animations to be done in this chunk
		std::vector<ChunkArray::Ptr> _chunkArrays;
	};

	std::vector<Chunk::Ptr> _chunks;
	mutable std::vector<Chunk*> _visibleChunks;

	Chunk::Ptr& getChunkAndTransform(int x, int y, sf::Vector2u& chunkRelative)
	{
		uint32_t chunkX = std::floor((x * _mapTileSize.x) / _chunkSize.x);
		uint32_t chunkY = std::floor((y * _mapTileSize.y) / _chunkSize.y);
		chunkRelative.x = ((x * _mapTileSize.x) - chunkX * _chunkSize.x) / _mapTileSize.x;
		chunkRelative.y = ((y * _mapTileSize.y) - chunkY * _chunkSize.y) / _mapTileSize.y;
		return _chunks[chunkX + static_cast<std::vector<Chunk::Ptr, std::allocator<Chunk::Ptr>>::size_type>(chunkY) * _chunkCount.x];
	}
};

}