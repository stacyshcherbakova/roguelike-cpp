#include "Music.h"
#include <MusicComponent.h>
#include <ResourceSystem.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Music::Music(const std::string& musicName, float volume)
	{
		gameObject = GameWorld::Instance()->CreateGameObject("Music: " + musicName);

		auto music = gameObject->AddComponent<MusicComponent>();
		if (music->Open(ResourceSystem::Instance()->GetMusicPath(musicName)))
		{
			music->SetLoop(true);
			music->SetVolume(volume);
			music->Play();
		}
	}
}
