#pragma once

#include "map/Map.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

#include <memory>
#include <string>
#include <unordered_map>

class b2World;

namespace sf
{
class Texture;
class Font;
}

namespace bgl
{

class AssetManager
{
public:
	static AssetManager& getInstance()
	{
		static AssetManager s_Instance;
		return s_Instance;
	}

	void loadTexture(const std::string& path, const std::string& id);
	void loadSoundBuffer(const std::string& path, const std::string& id);
	void loadMusic(const std::string& path, const std::string& id);
	void loadFont(const std::string& path, const std::string& id);
	void loadMap(const std::string& path, const std::string& id);

	const sf::Texture& getTexture(const std::string& id) const;
	sf::SoundBuffer& getSoundBuffer(const std::string& id) const;
	sf::Music& getMusic(const std::string& id) const;
	const sf::Font& getFont(const std::string& id) const;
	Map& getMap(const std::string& id) const;

	void unloadTexture(const std::string& id);
	void unloadSoundBuffer(const std::string& id);
	void unloadMusic(const std::string& id);
	void unloadFont(const std::string& id);
	void unloadMap(const std::string& id);

private:
	AssetManager() = default;

	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_TextureHolder;
	std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_SoundBufferHolder;
	std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_MusicHolder;
	std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_FontHolder;
	std::unordered_map<std::string, std::unique_ptr<Map>> m_MapHolder;
};
}
