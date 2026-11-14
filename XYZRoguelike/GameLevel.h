#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "Scene.h"
#include "Arena.h"
#include "Boss.h"
#include "Door.h"
#include "Enemy.h"
#include "Hud.h"
#include "LevelDefinition.h"
#include "Music.h"
#include "Player.h"
#include "Potion.h"

namespace XYZRoguelike
{
	// One location: an arena with enemies, a boss and a door that opens when all of them are dead
	class GameLevel : public XYZEngine::Scene
	{
	public:
		GameLevel(const LevelDefinition& definition, std::function<void()> onCompleted, std::function<void()> onPlayerDied,
			std::function<std::string()> hudStatus);

		void Start() override;
		void Restart() override;
		void Stop() override;

		const LevelDefinition& GetDefinition() const { return definition; }
		int GetAliveEnemies() const { return aliveEnemies; }
		bool IsBossAlive() const { return bossAlive; }
		Player* GetPlayer() const { return player.get(); }

	private:
		void SpawnEnemies();
		void SpawnBoss();
		void SpawnPotions();
		void OnEnemyDied();
		void OnBossDied();
		void OpenDoorIfClear();

		LevelDefinition definition;
		std::function<void()> onCompleted;
		std::function<void()> onPlayerDied;
		std::function<std::string()> hudStatus;

		std::unique_ptr<Arena> arena;
		std::unique_ptr<Player> player;
		std::unique_ptr<Door> door;
		std::vector<std::unique_ptr<Enemy>> enemies;
		std::unique_ptr<Boss> boss;
		std::vector<std::unique_ptr<Potion>> potions;
		std::unique_ptr<Music> music;
		std::unique_ptr<Hud> hud;
		int aliveEnemies = 0;
		bool bossAlive = false;
	};
}
