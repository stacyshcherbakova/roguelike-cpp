#include "DeveloperLevel.h"
#include "GameSettings.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		arena = std::make_unique<Arena>(Settings::ARENA_WIDTH, Settings::ARENA_HEIGHT);

		player = std::make_unique<Player>(arena->GetCenter());

		// The enemy starts a few tiles to the right, outside its detection radius
		const int enemyTileX = Settings::ARENA_WIDTH / 2 + Settings::ENEMY_START_TILE_OFFSET;
		enemy = std::make_unique<Enemy>(arena->TileToWorld(enemyTileX, Settings::ARENA_HEIGHT / 2), player->GetTransform());

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
		enemy.reset();
		player.reset();
		arena.reset();
		GameWorld::Instance()->Clear();
	}
}
