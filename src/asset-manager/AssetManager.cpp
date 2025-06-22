#include "asset-manager/AssetManager.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <spdlog/spdlog.h>

#include <map/Map.h>

namespace bgl
{

void AssetManager::loadTexture(const std::string& path, const std::string& id)
{
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(path))
	{
		SPDLOG_ERROR("Failed to load texture: " + path);
		return;
	}
	SPDLOG_INFO("Texture " + id + " loaded successfully : " + path);
	_textureHolder.try_emplace(id, std::move(texture));
}

void AssetManager::loadSoundBuffer(const std::string& path, const std::string& id)
{
	std::unique_ptr<sf::SoundBuffer> soundBuffer = std::make_unique<sf::SoundBuffer>();
	if (!soundBuffer->loadFromFile(path))
	{
		SPDLOG_ERROR("Failed to load sound buffer: " + path);
		return;
	}
	SPDLOG_INFO("Sound buffer " + id + " loaded successfully : " + path);
	_soundBufferHolder.try_emplace(id, std::move(soundBuffer));
}

void AssetManager::loadMusic(const std::string& path, const std::string& id)
{
	// Note: sf::Music is not loaded here, it's more like opened. The actual loading happens on play.
	std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
	if (!music->openFromFile(path))
	{
		SPDLOG_ERROR("Failed to open music file: " + path);
		return;
	}
	SPDLOG_INFO("Music " + id + " loaded successfully : " + path);
	_musicHolder.try_emplace(id, std::move(music));
}

void AssetManager::loadFont(const std::string& path, const std::string& id)
{
	std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
	if (!font->loadFromFile(path))
	{
		SPDLOG_ERROR("Failed to load font: " + path);
		return;
	}

	SPDLOG_INFO("Font " + id + " loaded successfully : " + path);
	_fontHolder.try_emplace(id, std::move(font));
}

void AssetManager::loadMap(const std::string& path, const std::string& id)
{
	std::unique_ptr<Map> map = std::make_unique<Map>();
	if (!map->loadFromFile(path))
	{
		SPDLOG_ERROR("Failed to load map: " + path);
		return;
	}
	SPDLOG_INFO("Map " + id + " loaded successfully : " + path);
	_mapHolder.try_emplace(id, std::move(map));
}

const sf::Texture& AssetManager::getTexture(const std::string& id) const
{
	auto found = _textureHolder.find(id);
	if (found == _textureHolder.end())
	{
		SPDLOG_ERROR("Cant find texture by id: " + id);
	}
	return *found->second;
}

sf::SoundBuffer& AssetManager::getSoundBuffer(const std::string& id) const
{
	auto found = _soundBufferHolder.find(id);
	if (found == _soundBufferHolder.end())
	{
		SPDLOG_ERROR("Cant find sound buffer by id: " + id);
	}
	return *found->second;
}

sf::Music& AssetManager::getMusic(const std::string& id) const
{
	auto found = _musicHolder.find(id);
	if (found == _musicHolder.end())
	{
		SPDLOG_ERROR("Cant find music by id: " + id);
	}
	return *found->second;
}

const sf::Font& AssetManager::getFont(const std::string& id) const
{
	auto found = _fontHolder.find(id);
	if (found == _fontHolder.end())
	{
		SPDLOG_ERROR("Cant find font by id: " + id);
	}
	return *found->second;
}

Map& AssetManager::getMap(const std::string& id) const
{
	auto found = _mapHolder.find(id);
	if (found == _mapHolder.end())
	{
		SPDLOG_ERROR("Cant find map by id: " + id);
	}
	return *found->second;
}

void AssetManager::unloadTexture(const std::string& id)
{
	_textureHolder.erase(id);
}

void AssetManager::unloadSoundBuffer(const std::string& id)
{
	_soundBufferHolder.erase(id);
}

void AssetManager::unloadMusic(const std::string& id)
{
	_musicHolder.erase(id);
}

void AssetManager::unloadFont(const std::string& id)
{
	_fontHolder.erase(id);
}

void AssetManager::unloadMap(const std::string& id)
{
	_mapHolder.erase(id);
}
}