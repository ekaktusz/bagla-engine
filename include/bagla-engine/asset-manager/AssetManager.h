#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace sf
{
	class Texture;
	class SoundBuffer;
	class Music;
}

namespace bgl
{
	class AssetManager
	{
	public:

		~AssetManager();

		static AssetManager& getInstance()
		{
			static AssetManager s_Instance;
			return s_Instance;
		}

		void loadTexture(const std::string& path, const std::string& id);
		void loadSoundBuffer(const std::string& path, const std::string& id);
		void loadMusic(const std::string& path, const std::string& id);

		const sf::Texture& getTexture(const std::string& id) const;
		sf::SoundBuffer& getSoundBuffer(const std::string& id) const;
		sf::Music& getMusic(const std::string& id) const;

		void unloadTexture(const std::string& id);
		void unloadSoundBuffer(const std::string& id);
		void unloadMusic(const std::string& id);

	private:
		AssetManager();

		std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_TextureHolder;
		std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_SoundBufferHolder;
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_MusicHolder;
	};
}
