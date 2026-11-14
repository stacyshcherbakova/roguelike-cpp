#include "pch.h"
#include "AudioComponent.h"

namespace XYZEngine
{
	AudioComponent::AudioComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	AudioComponent::~AudioComponent()
	{
		sound.stop();
	}

	void AudioComponent::Update(float deltaTime)
	{
	}

	void AudioComponent::Render()
	{
	}

	void AudioComponent::SetSound(const sf::SoundBuffer* buffer)
	{
		if (buffer != nullptr)
		{
			sound.setBuffer(*buffer);
		}
	}

	void AudioComponent::SetLoop(bool loop)
	{
		sound.setLoop(loop);
	}

	void AudioComponent::SetVolume(float volume)
	{
		sound.setVolume(volume);
	}

	void AudioComponent::Play()
	{
		if (sound.getBuffer() != nullptr && sound.getStatus() != sf::SoundSource::Playing)
		{
			sound.play();
		}
	}

	void AudioComponent::Stop()
	{
		sound.stop();
	}

	bool AudioComponent::IsPlaying() const
	{
		return sound.getStatus() == sf::SoundSource::Playing;
	}
}
