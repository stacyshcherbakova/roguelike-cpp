#pragma once

#include <string>
#include "Vector.h"

namespace XYZRoguelike
{
	// Tunable numbers of the game in one place
	namespace Settings
	{
		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 720;
		const std::string GAME_NAME = "XYZRoguelike";

		const std::string RESOURCES_PATH = "Resources/";
#ifdef NDEBUG
		const bool DRAW_COLLIDERS = false;
#else
		const bool DRAW_COLLIDERS = true;
#endif

		// Player
		const std::string PLAYER_TEXTURE_MAP = "player";
		const XYZEngine::Vector2Di PLAYER_SIZE = { 72, 96 };
		const float PLAYER_SPEED = 400.f;
		const float PLAYER_ANIMATION_FPS = 8.f;

		// Enemy
		const std::string ENEMY_TEXTURE = "enemy";
		const XYZEngine::Vector2Di ENEMY_SIZE = { 80, 80 };
		const float ENEMY_SPEED = 230.f;
		const float ENEMY_DETECTION_RADIUS = 450.f;
		const float ENEMY_STOP_DISTANCE = 60.f;
		const int ENEMY_START_TILE_OFFSET = 5;

		// Level
		const int TILE_SIZE = 128;
		const std::string FLOOR_TEXTURE_MAP = "level_floors";
		const std::string WALL_TEXTURE_MAP = "level_walls";
		const int FLOOR_TILE = 0;
		const int WALL_TILE = 14;
		const int ARENA_WIDTH = 14;
		const int ARENA_HEIGHT = 10;

		// Audio
		const std::string MUSIC_NAME = "theme";
		const float MUSIC_VOLUME = 40.f;
	}
}
