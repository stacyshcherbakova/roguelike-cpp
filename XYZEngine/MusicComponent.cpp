#include "pch.h"
#include "MusicComponent.h"

namespace XYZEngine
{
	MusicComponent::MusicComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	MusicComponent::~MusicComponent()
	{
		music.stop();
	}

	void MusicComponent::Update(float deltaTime)
	{
	}

	void MusicComponent::Render()
	{
	}

	bool MusicComponent::Open(const std::string& filePath)
	{
		isOpened = music.openFromFile(filePath);
		return isOpened;
	}

	void MusicComponent::SetLoop(bool loop)
	{
		music.setLoop(loop);
	}

	void MusicComponent::SetVolume(float volume)
	{
		music.setVolume(volume);
	}

	void MusicComponent::Play()
	{
		if (isOpened && music.getStatus() != sf::SoundSource::Playing)
		{
			music.play();
		}
	}

	void MusicComponent::Stop()
	{
		music.stop();
	}

	bool MusicComponent::IsPlaying() const
	{
		return music.getStatus() == sf::SoundSource::Playing;
	}
}
