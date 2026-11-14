#include "Arena.h"
#include "GameSettings.h"
#include <Logger.h>
#include <algorithm>
#include <stdexcept>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Arena::Arena(int widthInTiles, int heightInTiles, int floorTile, int wallTile, const std::vector<Vector2Di>& openings)
		: width(widthInTiles)
		, height(heightInTiles)
	{
		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Arena size must be positive");
		}
		LOG_INFO("Building an arena of " << width << "x" << height << " tiles with " << openings.size() << " openings");

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				floors.push_back(std::make_unique<Floor>(TileToWorld(x, y), floorTile));
			}
		}

		auto isOpening = [&openings](int x, int y) {
			return std::find(openings.begin(), openings.end(), Vector2Di{ x, y }) != openings.end();
		};
		auto addWall = [&](int x, int y) {
			if (!isOpening(x, y))
			{
				walls.push_back(std::make_unique<Wall>(TileToWorld(x, y), wallTile));
			}
		};

		// Walls sit one tile outside the floor on every side, corners included
		for (int x = -1; x <= width; x++)
		{
			addWall(x, -1);
			addWall(x, height);
		}
		for (int y = 0; y < height; y++)
		{
			addWall(-1, y);
			addWall(width, y);
		}
	}

	Vector2Df Arena::GetCenter() const
	{
		return TileToWorld(width / 2, height / 2);
	}

	Vector2Df Arena::TileToWorld(int x, int y) const
	{
		return { x * (float)Settings::TILE_SIZE, y * (float)Settings::TILE_SIZE };
	}
}
