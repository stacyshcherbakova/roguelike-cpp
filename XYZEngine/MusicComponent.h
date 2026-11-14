#pragma once

#include <SFML/Audio/Music.hpp>
#include <string>
#include "Component.h"

namespace XYZEngine
{
	// Streams a long track from disk; the file path comes from the ResourceSystem
	class MusicComponent : public Component
	{
	public:
		MusicComponent(GameObject* gameObject);
		~MusicComponent();

		void Update(float deltaTime) override;
		void Render() override;

		bool Open(const std::string& filePath);
		void SetLoop(bool loop);
		void SetVolume(float volume);

		void Play();
		void Stop();
		bool IsPlaying() const;

	private:
		sf::Music music;
		bool isOpened = false;
	};
}
