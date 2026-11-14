#pragma once

#include <memory>
#include <vector>
#include "Scene.h"
#include "Arena.h"
#include "Enemy.h"
#include "Music.h"
#include "Player.h"

namespace XYZRoguelike
{
	class DeveloperLevel : public XYZEngine::Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;

	private:
		void SpawnEnemies();

		std::unique_ptr<Arena> arena;
		std::unique_ptr<Player> player;
		std::vector<std::unique_ptr<Enemy>> enemies;
		std::unique_ptr<Music> music;
	};
}
