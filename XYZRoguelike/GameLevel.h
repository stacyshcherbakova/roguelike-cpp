#pragma once

#include <functional>
#include <memory>
#include <vector>
#include "Scene.h"
#include "Arena.h"
#include "Boss.h"
#include "Door.h"
#include "Enemy.h"
#include "LevelDefinition.h"
#include "Music.h"
#include "Player.h"

namespace XYZRoguelike
{
	// One location: an arena with enemies and a door that opens when every enemy is dead
	class GameLevel : public XYZEngine::Scene
	{
	public:
		GameLevel(const LevelDefinition& definition, std::function<void()> onCompleted, std::function<void()> onPlayerDied);

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
		void OnEnemyDied();
		void OnBossDied();
		void OpenDoorIfClear();

		LevelDefinition definition;
		std::function<void()> onCompleted;
		std::function<void()> onPlayerDied;

		std::unique_ptr<Arena> arena;
		std::unique_ptr<Player> player;
		std::unique_ptr<Door> door;
		std::vector<std::unique_ptr<Enemy>> enemies;
		std::unique_ptr<Boss> boss;
		std::unique_ptr<Music> music;
		int aliveEnemies = 0;
		bool bossAlive = false;
	};
}
