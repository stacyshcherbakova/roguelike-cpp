#include "DeveloperLevel.h"
#include "GameSettings.h"
#include <Logger.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		LOG_INFO("Starting the developer level");

		arena = std::make_unique<Arena>(Settings::ARENA_WIDTH, Settings::ARENA_HEIGHT);

		player = std::make_unique<Player>(arena->GetCenter());
		player->GetHealth()->SetOnDeath([this]() {
			LOG_WARNING("The player is dead, the level restarts at the end of the frame");
			GameWorld::Instance()->RunLater([this]() { Restart(); });
		});

		SpawnEnemies();

		music = std::make_unique<Music>(Settings::MUSIC_NAME, Settings::MUSIC_VOLUME);
	}

	void DeveloperLevel::SpawnEnemies()
	{
		// Enemies start a few tiles away from the centre, outside their detection radius
		const int centerX = Settings::ARENA_WIDTH / 2;
		const int centerY = Settings::ARENA_HEIGHT / 2;
		const int offset = Settings::ENEMY_START_TILE_OFFSET;
		const XYZEngine::Vector2Di tiles[] = {
			{ centerX + offset, centerY },
			{ centerX - offset, centerY + 2 },
			{ centerX + 2, centerY - offset + 1 },
		};

		for (const auto& tile : tiles)
		{
			enemies.push_back(std::make_unique<Enemy>(arena->TileToWorld(tile.x, tile.y), player->GetGameObject()));
		}
	}

	void DeveloperLevel::Restart()
	{
		LOG_INFO("Restarting the developer level");
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		music.reset();
		enemies.clear();
		player.reset();
		arena.reset();
		GameWorld::Instance()->Clear();
	}
}
