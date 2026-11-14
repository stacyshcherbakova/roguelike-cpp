#pragma once

#include <memory>
#include <string>
#include <vector>
#include "GameLevel.h"
#include "Hud.h"
#include "LevelDefinition.h"

namespace XYZRoguelike
{
	// Game flow: the list of locations, which one is active, the victory screen and the HUD text
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
		void ShowVictory();
		void OnLevelCompleted();
		void OnPlayerDied();
		std::string BuildHudStatus() const;

		std::vector<LevelDefinition> levels;
		int currentLevel = 0;
		int deaths = 0;
		std::unique_ptr<GameLevel> level;
		std::unique_ptr<Hud> victoryScreen;
	};
}
