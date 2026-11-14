#include "GameLevel.h"
#include "GameSettings.h"
#include <KeyActionComponent.h>
#include <Logger.h>
#include <randomizer.h>
#include <algorithm>

using namespace XYZEngine;

namespace XYZRoguelike
{
	GameLevel::GameLevel(const LevelDefinition& definition, std::function<void()> onCompleted, std::function<void()> onPlayerDied,
		std::function<std::string()> hudStatus)
		: definition(definition)
		, onCompleted(std::move(onCompleted))
		, onPlayerDied(std::move(onPlayerDied))
		, hudStatus(std::move(hudStatus))
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

		SpawnPotions();

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
			auto debugKey = player->GetGameObject()->AddComponent<KeyActionComponent>();
			debugKey->Bind(sf::Keyboard::F2, [this]() {
				LOG_WARNING("Debug key: the door is forced open");
				door->SetOpen(true);
			});
		}

		SpawnEnemies();
		SpawnBoss();
		OpenDoorIfClear();

		music = std::make_unique<Music>(Settings::MUSIC_NAME, Settings::MUSIC_VOLUME);

		// The HUD is created last so it is drawn above everything else
		hud = std::make_unique<Hud>(hudStatus, Settings::HUD_HINT);
	}

	void GameLevel::SpawnPotions()
	{
		for (int i = 0; i < definition.potionCount; i++)
		{
			const int x = random<int>(1, definition.width - 2);
			const int y = random<int>(0, definition.height - 1);
			potions.push_back(std::make_unique<Potion>(arena->TileToWorld(x, y)));
		}
	}

	void GameLevel::SpawnEnemies()
	{
		aliveEnemies = 0;
		// Enemies appear in the right two thirds of the room, away from the player's start
		const int minX = std::max(2, definition.width / 3);
		// Every monster gets a tile of its own: two bodies created in the same place would be stuck in each other
		std::vector<Vector2Di> takenTiles = { GetBossTile() };
		const int maxAttempts = 100;
		for (int i = 0; i < definition.enemyCount; i++)
		{
			Vector2Di tile;
			int attempts = 0;
			do
			{
				tile = { random<int>(minX, definition.width - 1), random<int>(0, definition.height - 1) };
				attempts++;
			} while (attempts < maxAttempts && std::find(takenTiles.begin(), takenTiles.end(), tile) != takenTiles.end());
			takenTiles.push_back(tile);

			enemies.push_back(std::make_unique<Enemy>(arena->TileToWorld(tile), player->GetGameObject(), [this]() { OnEnemyDied(); }));
			aliveEnemies++;
		}
	}

	Vector2Di GameLevel::GetBossTile() const
	{
		// The boss guards the door from two tiles inside the room
		return { definition.width - 2, definition.height / 2 };
	}

	void GameLevel::SpawnBoss()
	{
		bossAlive = false;
		if (definition.bossHealthScale <= 0.f)
		{
			return;
		}

		boss = std::make_unique<Boss>(arena->TileToWorld(GetBossTile()), player->GetGameObject(), definition.bossHealthScale, [this]() { OnBossDied(); });
		bossAlive = true;
	}

	void GameLevel::OnEnemyDied()
	{
		aliveEnemies--;
		LOG_INFO("Enemies left on '" << definition.name << "': " << aliveEnemies);
		OpenDoorIfClear();
	}

	void GameLevel::OnBossDied()
	{
		bossAlive = false;
		LOG_INFO("The boss of '" << definition.name << "' is defeated");
		OpenDoorIfClear();
	}

	void GameLevel::OpenDoorIfClear()
	{
		if (door && !door->IsOpen() && aliveEnemies <= 0 && !bossAlive)
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
		hud.reset();
		music.reset();
		potions.clear();
		boss.reset();
		enemies.clear();
		door.reset();
		player.reset();
		arena.reset();
		GameWorld::Instance()->Clear();
	}
}
