#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace XYZEngine
{
	// Owns every texture, sound and music path of the game.
	// A missing texture is reported through the logger and replaced by a bright fallback texture,
	// so a broken resource never stops the game.
	class ResourceSystem
	{
	public:
		static ResourceSystem* Instance();

		bool LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth = true);
		const sf::Texture* GetTextureShared(const std::string& name) const;
		sf::Texture* GetTextureCopy(const std::string& name) const;
		void DeleteSharedTexture(const std::string& name);

		// Throws std::invalid_argument when the element size or count makes no sense
		bool LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth = true);
		const sf::Texture* GetTextureMapElementShared(const std::string& name, int elementIndex) const;
		sf::Texture* GetTextureMapElementCopy(const std::string& name, int elementIndex) const;
		int GetTextureMapElementsCount(const std::string& name) const;
		void DeleteSharedTextureMap(const std::string& name);

		// Short sounds are kept in memory, music is streamed so only its path is stored
		bool LoadSound(const std::string& name, std::string sourcePath);
		const sf::SoundBuffer* GetSound(const std::string& name) const;
		void DeleteSound(const std::string& name);

		void RegisterMusic(const std::string& name, std::string sourcePath);
		std::string GetMusicPath(const std::string& name) const;

		bool LoadFont(const std::string& name, std::string sourcePath);
		const sf::Font* GetFont(const std::string& name) const;

		// Magenta texture returned instead of anything that failed to load
		const sf::Texture* GetFallbackTexture() const;

		void Clear();

	private:
		std::map<std::string, sf::Texture*> textures;
		std::map<std::string, std::vector<sf::Texture*>> textureMaps;
		std::map<std::string, sf::SoundBuffer*> sounds;
		std::map<std::string, std::string> musicPaths;
		std::map<std::string, sf::Font*> fonts;
		mutable sf::Texture* fallbackTexture = nullptr;

		ResourceSystem() {}
		~ResourceSystem() {}

		ResourceSystem(ResourceSystem const&) = delete;
		ResourceSystem& operator= (ResourceSystem const&) = delete;

		void DeleteAllTextures();
		void DeleteAllTextureMaps();
		void DeleteAllSounds();
		void DeleteAllFonts();
	};
}
