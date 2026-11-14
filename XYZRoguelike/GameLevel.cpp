#include "GameLevel.h"
#include "DebugKeysComponent.h"
#include "GameSettings.h"
#include <Logger.h>
#include <randomizer.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	GameLevel::GameLevel(const LevelDefinition& definition, std::function<void()> onCompleted, std::function<void()> onPlayerDied)
		: definition(definition)
		, onCompleted(std::move(onCompleted))
		, onPlayerDied(std::move(onPlayerDied))
	{
	}

	void GameLevel::Start()
	{
		LOG_INFO("Starting level '" << definition.name << "' (" << definition.width << "x" << definition.height << ", " << definition.enemyCount << " enemies)");

		// The door replaces the middle wall tile of the right side
		const Vector2Di doorTile = { definition.width, definition.height / 2 };
		arena = std::make_unique<Arena>(definition.width, definition.height, definition.floorTile, definition.wallTile, std::vector<Vector2Di>{ doorTile });

		door = std::make_unique<Door>(arena->TileToWorld(doorTile));
		door->SetOnPlayerEnter([this]() {
			if (onCompleted)
			{
				onCompleted();
			}
		});

		player = std::make_unique<Player>(arena->TileToWorld(1, definition.height / 2));
		player->GetHealth()->SetOnDeath([this]() {
			LOG_WARNING("The player is dead");
			if (onPlayerDied)
			{
				onPlayerDied();
			}
		});

		if (Settings::DEBUG_KEYS)
		{
			auto debugKeys = player->GetGameObject()->AddComponent<DebugKeysComponent>();
			debugKeys->SetOnOpenDoor([this]() { door->SetOpen(true); });
		}

		SpawnEnemies();
		if (aliveEnemies == 0)
		{
			door->SetOpen(true);
		}

		music = std::make_unique<Music>(Settings::MUSIC_NAME, Settings::MUSIC_VOLUME);
	}

	void GameLevel::SpawnEnemies()
	{
		aliveEnemies = 0;
		// Enemies appear in the right two thirds of the room, away from the player's start
		const int minX = std::max(2, definition.width / 3);
		for (int i = 0; i < definition.enemyCount; i++)
		{
			const int x = random<int>(minX, definition.width - 1);
			const int y = random<int>(0, definition.height - 1);
			enemies.push_back(std::make_unique<Enemy>(arena->TileToWorld(x, y), player->GetGameObject(), [this]() { OnEnemyDied(); }));
			aliveEnemies++;
		}
	}

	void GameLevel::OnEnemyDied()
	{
		aliveEnemies--;
		LOG_INFO("Enemies left on '" << definition.name << "': " << aliveEnemies);
		if (aliveEnemies <= 0 && door)
		{
			door->SetOpen(true);
		}
	}

	void GameLevel::Restart()
	{
		LOG_INFO("Restarting level '" << definition.name << "'");
		Stop();
		Start();
	}

	void GameLevel::Stop()
	{
		music.reset();
		enemies.clear();
		door.reset();
		player.reset();
		arena.reset();
		GameWorld::Instance()->Clear();
	}
}
