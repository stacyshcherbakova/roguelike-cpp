#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Component.h"

namespace XYZEngine
{
	// Plays a short sound loaded into memory by the ResourceSystem
	class AudioComponent : public Component
	{
	public:
		AudioComponent(GameObject* gameObject);
		~AudioComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetSound(const sf::SoundBuffer* buffer);
		void SetLoop(bool loop);
		void SetVolume(float volume);

		void Play();
		void Stop();
		bool IsPlaying() const;

	private:
		sf::Sound sound;
	};
}
