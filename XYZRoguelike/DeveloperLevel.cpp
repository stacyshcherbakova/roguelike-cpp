#include "DeveloperLevel.h"
#include "GameSettings.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		player = std::make_unique<Player>(Vector2Df{ 0.f, 0.f });
		music = std::make_unique<Music>(Settings::MUSIC_NAME, Settings::MUSIC_VOLUME);
	}

	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		music.reset();
		player.reset();
		GameWorld::Instance()->Clear();
	}
}
