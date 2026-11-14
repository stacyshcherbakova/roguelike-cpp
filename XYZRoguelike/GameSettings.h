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
		const bool DEBUG_KEYS = false;
#else
		const bool DRAW_COLLIDERS = true;
		const bool DEBUG_KEYS = true;
#endif

		// Player
		const std::string PLAYER_OBJECT_NAME = "Player";
		const std::string PLAYER_TEXTURE_MAP = "player";
		const XYZEngine::Vector2Di PLAYER_SIZE = { 72, 96 };
		const float PLAYER_SPEED = 400.f;
		const float PLAYER_ANIMATION_FPS = 8.f;
		const float PLAYER_HEALTH = 100.f;
		const float PLAYER_ARMOR = 5.f;
		const float PLAYER_DAMAGE = 20.f;
		const float PLAYER_ATTACK_RANGE = 140.f;
		const float PLAYER_ATTACK_COOLDOWN = 0.4f;

		// Enemy
		const std::string ENEMY_OBJECT_NAME = "Enemy";
		const std::string ENEMY_TEXTURE = "enemy";
		const XYZEngine::Vector2Di ENEMY_SIZE = { 80, 80 };
		const float ENEMY_SPEED = 230.f;
		const float ENEMY_DETECTION_RADIUS = 450.f;
		const float ENEMY_STOP_DISTANCE = 60.f;
		const int ENEMY_START_TILE_OFFSET = 5;
		const float ENEMY_HEALTH = 50.f;
		const float ENEMY_ARMOR = 2.f;
		const float ENEMY_DAMAGE = 12.f;
		const float ENEMY_ATTACK_RANGE = 110.f;
		const float ENEMY_ATTACK_COOLDOWN = 1.f;

		// Level
		const int TILE_SIZE = 128;
		const std::string FLOOR_TEXTURE_MAP = "level_floors";
		const std::string WALL_TEXTURE_MAP = "level_walls";
		const std::string DOOR_OBJECT_NAME = "Door";
		const std::string DOOR_CLOSED_TEXTURE = "door_closed";
		const std::string DOOR_OPEN_TEXTURE = "door_open";

		// Audio
		const std::string MUSIC_NAME = "theme";
		const float MUSIC_VOLUME = 40.f;
		const std::string HIT_SOUND = "hit";
		const std::string DEATH_SOUND = "death";
	}
}
