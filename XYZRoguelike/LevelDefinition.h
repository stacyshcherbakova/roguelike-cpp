#pragma once

#include <string>

namespace XYZRoguelike
{
	// Static description of one location of the game
	struct LevelDefinition
	{
		std::string name;
		int width = 10;
		int height = 8;
		int enemyCount = 3;
		int floorTile = 0;
		int wallTile = 14;
		// Boss health relative to the base value; 0 means the level has no boss
		float bossHealthScale = 1.f;
		int potionCount = 2;
	};
}
