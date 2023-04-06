#include "asset-manager/AssetManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <spdlog/spdlog.h>

#include <map/Map.h>

namespace bgl
{
	AssetManager::AssetManager()
	{

	}

	AssetManager::~AssetManager()
	{

	}

	void AssetManager::loadTexture(const std::string& path, const std::string& id)
	{
		std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
		if (!texture->loadFromFile(path))
		{
			spdlog::error("Failed to load texture: " + path);
			return;
		}
		spdlog::info("Texture " + id + " loaded successfully : " + path);
		m_TextureHolder.try_emplace(id, std::move(texture));
	}

	void AssetManager::loadSoundBuffer(const std::string& path, const std::string& id)
	{
		std::unique_ptr<sf::SoundBuffer> soundBuffer = std::make_unique<sf::SoundBuffer>();
		if (!soundBuffer->loadFromFile(path))
		{
			spdlog::error("Failed to load sound buffer: " + path);
			return;
		}
		spdlog::info("Sound buffer " + id + " loaded successfully : " + path);
		m_SoundBufferHolder.try_emplace(id, std::move(soundBuffer));
	}

	void AssetManager::loadMusic(const std::string& path, const std::string& id)
	{
		// Note: sf::Music is not loaded here, it's more like opened. The actual loading happens on play.
		std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
		if (!music->openFromFile(path))
		{
			spdlog::error("Failed to open music file: " + path);
			return;
		}
		spdlog::info("Music " + id + " loaded successfully : " + path);
		m_MusicHolder.try_emplace(id, std::move(music));
	}

	void AssetManager::loadFont(const std::string& path, const std::string& id)
	{
		std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
		if (!font->loadFromFile(path))
		{
			spdlog::error("Failed to load font: " + path);
			return;
		}
		spdlog::info("Font " + id + " loaded successfully : " + path);
		m_FontHolder.try_emplace(id, std::move(font));
	}
	
	void AssetManager::loadMap(const std::string& path, const std::string& id, b2World* world)
	{
		std::unique_ptr<Map> map = std::make_unique<Map>();
		if (!map->loadFromFile(path, world))
		{
			spdlog::error("Failed to load map: " + path);
			return;
		}
		spdlog::info("Map " + id + " loaded successfully : " + path);
		m_MapHolder.try_emplace(id, std::move(map));
	}

	const sf::Texture& AssetManager::getTexture(const std::string& id) const
	{
		auto found = m_TextureHolder.find(id);
		if (found == m_TextureHolder.end())
		{
			spdlog::error("Cant find texture by id: " + id);
		}
		return *found->second;
	}

	sf::SoundBuffer& AssetManager::getSoundBuffer(const std::string& id) const
	{
		auto found = m_SoundBufferHolder.find(id);
		if (found == m_SoundBufferHolder.end())
		{
			spdlog::error("Cant find sound buffer by id: " + id);
		}
		return *found->second;
	}

	sf::Music& AssetManager::getMusic(const std::string& id)
	{
		auto found = m_MusicHolder.find(id);
		if (found == m_MusicHolder.end())
		{
			spdlog::error("Cant find music by id: " + id);
		}
		return *found->second;
	}

	const sf::Font& AssetManager::getFont(const std::string& id) const
	{
		auto found = m_FontHolder.find(id);
		if (found == m_FontHolder.end())
		{
			spdlog::error("Cant find font by id: " + id);
		}
		return *found->second;
	}

	Map& AssetManager::getMap(const std::string& id) const
	{
		auto found = m_MapHolder.find(id);
		if (found == m_MapHolder.end())
		{
			spdlog::error("Cant find map by id: " + id);
		}
		return *found->second;
	}

	void AssetManager::unloadTexture(const std::string& id)
	{
		m_TextureHolder.erase(id);
	}

	void AssetManager::unloadSoundBuffer(const std::string& id)
	{
		m_SoundBufferHolder.erase(id);
	}

	void AssetManager::unloadMusic(const std::string& id)
	{
		m_MusicHolder.erase(id);
	}

	void AssetManager::unloadFont(const std::string& id)
	{
		m_FontHolder.erase(id);
	}

	void AssetManager::unloadMap(const std::string& id)
	{
		m_MapHolder.erase(id);
	}

}