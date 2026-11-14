#include "RoguelikeGame.h"
#include "GameSettings.h"
#include <GameWorld.h>
#include <Logger.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	RoguelikeGame::RoguelikeGame()
	{
		levels = {
			{ "Cellar", 12, 9, 3, 0, 14 },
			{ "Catacombs", 16, 11, 5, 8, 26 },
			{ "Throne hall", 20, 13, 7, 40, 38 },
		};
	}

	void RoguelikeGame::Start()
	{
		StartLevel(0);
	}

	void RoguelikeGame::Stop()
	{
		if (level)
		{
			level->Stop();
			level.reset();
		}
	}

	void RoguelikeGame::StartLevel(int index)
	{
		if (level)
		{
			level->Stop();
		}
		currentLevel = index;
		level = std::make_unique<GameLevel>(levels[index], [this]() { OnLevelCompleted(); }, [this]() { OnPlayerDied(); });
		level->Start();
		LOG_INFO("Level " << (index + 1) << " of " << levels.size() << " is running");
	}

	void RoguelikeGame::OnLevelCompleted()
	{
		// Scene changes are deferred to the end of the frame: the callback comes from inside a component update
		const int next = currentLevel + 1;
		if (next < (int)levels.size())
		{
			LOG_INFO("Level '" << levels[currentLevel].name << "' completed, loading the next one");
			GameWorld::Instance()->RunLater([this, next]() { StartLevel(next); });
		}
		else
		{
			LOG_INFO("The last level is completed, the game starts over");
			GameWorld::Instance()->RunLater([this]() { StartLevel(0); });
		}
	}

	void RoguelikeGame::OnPlayerDied()
	{
		LOG_WARNING("Level '" << levels[currentLevel].name << "' restarts because the player died");
		GameWorld::Instance()->RunLater([this]() { level->Restart(); });
	}
}
