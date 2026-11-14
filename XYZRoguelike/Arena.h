#pragma once

#include <memory>
#include <vector>
#include "Floor.h"
#include "Wall.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Rectangular room: floor tiles inside, a ring of walls around.
	// Tiles are placed on a grid so they never overlap; floors are created first so walls draw on top of them.
	class Arena
	{
	public:
		Arena(int widthInTiles, int heightInTiles);

		XYZEngine::Vector2Df GetCenter() const;
		// World position of the centre of a tile; (0, 0) is the bottom-left floor tile
		XYZEngine::Vector2Df TileToWorld(int x, int y) const;
		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

	private:
		int width;
		int height;
		std::vector<std::unique_ptr<Floor>> floors;
		std::vector<std::unique_ptr<Wall>> walls;
	};
}
