#pragma once

#include <memory>
#include <vector>
#include "GameLevel.h"
#include "LevelDefinition.h"

namespace XYZRoguelike
{
	// Game flow: the list of locations, which one is active and what happens when it ends
	class RoguelikeGame
	{
	public:
		RoguelikeGame();

		void Start();
		void Stop();

		int GetLevelIndex() const { return currentLevel; }
		int GetLevelCount() const { return (int)levels.size(); }
		GameLevel* GetLevel() const { return level.get(); }

	private:
		void StartLevel(int index);
		void OnLevelCompleted();
		void OnPlayerDied();

		std::vector<LevelDefinition> levels;
		int currentLevel = 0;
		std::unique_ptr<GameLevel> level;
	};
}
