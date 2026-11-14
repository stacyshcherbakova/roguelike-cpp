#include "Arena.h"
#include "GameSettings.h"
#include <Logger.h>
#include <stdexcept>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Arena::Arena(int widthInTiles, int heightInTiles)
		: width(widthInTiles)
		, height(heightInTiles)
	{
		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Arena size must be positive");
		}
		LOG_INFO("Building an arena of " << width << "x" << height << " tiles");

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				floors.push_back(std::make_unique<Floor>(TileToWorld(x, y), Settings::FLOOR_TILE));
			}
		}

		// Walls sit one tile outside the floor on every side, corners included
		for (int x = -1; x <= width; x++)
		{
			walls.push_back(std::make_unique<Wall>(TileToWorld(x, -1), Settings::WALL_TILE));
			walls.push_back(std::make_unique<Wall>(TileToWorld(x, height), Settings::WALL_TILE));
		}
		for (int y = 0; y < height; y++)
		{
			walls.push_back(std::make_unique<Wall>(TileToWorld(-1, y), Settings::WALL_TILE));
			walls.push_back(std::make_unique<Wall>(TileToWorld(width, y), Settings::WALL_TILE));
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
