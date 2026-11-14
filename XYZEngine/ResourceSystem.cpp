#include "pch.h"
#include "ResourceSystem.h"
#include "Logger.h"

#include <cassert>
#include <stdexcept>

namespace XYZEngine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	bool ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.find(name) != textures.end())
		{
			LOG_WARNING("Texture '" << name << "' is already loaded, skipping " << sourcePath);
			return true;
		}

		sf::Texture* newTexture = new sf::Texture();
		if (!newTexture->loadFromFile(sourcePath))
		{
			LOG_ERROR("Failed to load texture '" << name << "' from " << sourcePath);
			delete newTexture;
			return false;
		}

		newTexture->setSmooth(isSmooth);
		textures.emplace(name, newTexture);
		LOG_INFO("Texture '" << name << "' loaded from " << sourcePath);
		return true;
	}
	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		auto texturePair = textures.find(name);
		if (texturePair == textures.end())
		{
			LOG_ERROR("Texture '" << name << "' was never loaded, using the fallback texture");
			return GetFallbackTexture();
		}
		return texturePair->second;
	}
	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		return new sf::Texture(*GetTextureShared(name));
	}
	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		auto texturePair = textures.find(name);
		if (texturePair == textures.end())
		{
			LOG_WARNING("Texture '" << name << "' cannot be deleted because it is not loaded");
			return;
		}

		sf::Texture* deletingTexure = texturePair->second;
		textures.erase(texturePair);
		delete deletingTexure;
	}

	bool ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		if (elementPixelSize.x == 0 || elementPixelSize.y == 0)
		{
			throw std::invalid_argument("Texture map '" + name + "' has a zero element size");
		}
		if (totalElements <= 0)
		{
			throw std::invalid_argument("Texture map '" + name + "' must have at least one element");
		}

		if (textureMaps.find(name) != textureMaps.end())
		{
			LOG_WARNING("Texture map '" << name << "' is already loaded, skipping " << sourcePath);
			return true;
		}

		sf::Texture textureMap;
		if (!textureMap.loadFromFile(sourcePath))
		{
			LOG_ERROR("Failed to load texture map '" << name << "' from " << sourcePath);
			return false;
		}

		std::vector<sf::Texture*> textureMapElements;
		const auto textureSize = textureMap.getSize();
		int loadedElements = 0;

		for (unsigned int y = 0; y + elementPixelSize.y <= textureSize.y && loadedElements < totalElements; y += elementPixelSize.y)
		{
			for (unsigned int x = 0; x + elementPixelSize.x <= textureSize.x && loadedElements < totalElements; x += elementPixelSize.x)
			{
				sf::Texture* newTextureMapElement = new sf::Texture();
				if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
				{
					newTextureMapElement->setSmooth(isSmooth);
					textureMapElements.push_back(newTextureMapElement);
				}
				else
				{
					delete newTextureMapElement;
				}
				loadedElements++;
			}
		}

		if ((int)textureMapElements.size() < totalElements)
		{
			LOG_WARNING("Texture map '" << name << "' has only " << textureMapElements.size() << " elements of " << totalElements << " requested");
		}
		if (textureMapElements.empty())
		{
			LOG_ERROR("Texture map '" << name << "' contains no elements of size " << elementPixelSize.x << "x" << elementPixelSize.y);
			return false;
		}

		textureMaps.emplace(name, std::move(textureMapElements));
		LOG_INFO("Texture map '" << name << "' loaded from " << sourcePath << " (" << textureMaps[name].size() << " elements)");
		return true;
	}
	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			LOG_ERROR("Texture map '" << name << "' was never loaded, using the fallback texture");
			return GetFallbackTexture();
		}

		const auto& elements = textureMap->second;
		if (elementIndex < 0 || elementIndex >= (int)elements.size())
		{
			LOG_ERROR("Texture map '" << name << "' has no element " << elementIndex << " (size " << elements.size() << "), using the fallback texture");
			return GetFallbackTexture();
		}
		return elements[elementIndex];
	}
	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		return new sf::Texture(*GetTextureMapElementShared(name, elementIndex));
	}
	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			LOG_WARNING("Texture map '" << name << "' was never loaded, element count is 0");
			return 0;
		}
		return (int)textureMap->second.size();
	}
	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			LOG_WARNING("Texture map '" << name << "' cannot be deleted because it is not loaded");
			return;
		}

		for (auto texture : textureMap->second)
		{
			delete texture;
		}
		textureMaps.erase(textureMap);
	}

	bool ResourceSystem::LoadSound(const std::string& name, std::string sourcePath)
	{
		if (sounds.find(name) != sounds.end())
		{
			LOG_WARNING("Sound '" << name << "' is already loaded, skipping " << sourcePath);
			return true;
		}

		sf::SoundBuffer* newSound = new sf::SoundBuffer();
		if (!newSound->loadFromFile(sourcePath))
		{
			LOG_ERROR("Failed to load sound '" << name << "' from " << sourcePath);
			delete newSound;
			return false;
		}

		sounds.emplace(name, newSound);
		LOG_INFO("Sound '" << name << "' loaded from " << sourcePath);
		return true;
	}
	const sf::SoundBuffer* ResourceSystem::GetSound(const std::string& name) const
	{
		auto soundPair = sounds.find(name);
		if (soundPair == sounds.end())
		{
			LOG_ERROR("Sound '" << name << "' was never loaded");
			return nullptr;
		}
		return soundPair->second;
	}
	void ResourceSystem::DeleteSound(const std::string& name)
	{
		auto soundPair = sounds.find(name);
		if (soundPair == sounds.end())
		{
			LOG_WARNING("Sound '" << name << "' cannot be deleted because it is not loaded");
			return;
		}

		sf::SoundBuffer* deletingSound = soundPair->second;
		sounds.erase(soundPair);
		delete deletingSound;
	}

	void ResourceSystem::RegisterMusic(const std::string& name, std::string sourcePath)
	{
		musicPaths[name] = sourcePath;
		LOG_INFO("Music '" << name << "' registered at " << sourcePath);
	}
	std::string ResourceSystem::GetMusicPath(const std::string& name) const
	{
		auto musicPair = musicPaths.find(name);
		if (musicPair == musicPaths.end())
		{
			LOG_ERROR("Music '" << name << "' was never registered");
			return std::string();
		}
		return musicPair->second;
	}

	const sf::Texture* ResourceSystem::GetFallbackTexture() const
	{
		if (fallbackTexture == nullptr)
		{
			sf::Image image;
			image.create(32, 32, sf::Color::Magenta);
			fallbackTexture = new sf::Texture();
			const bool created = fallbackTexture->loadFromImage(image);
			assert(created && "The fallback texture must always be creatable");
		}
		return fallbackTexture;
	}

	void ResourceSystem::Clear()
	{
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllSounds();
		musicPaths.clear();
		LOG_INFO("All resources released");
	}

	void ResourceSystem::DeleteAllTextures()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& texturePair : textures)
		{
			keysToDelete.push_back(texturePair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTexture(key);
		}
	}
	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}
	void ResourceSystem::DeleteAllSounds()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& soundPair : sounds)
		{
			keysToDelete.push_back(soundPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSound(key);
		}
	}
}
