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
	};
}
