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

		const std::string PLAYER_TEXTURE_MAP = "player";
		const XYZEngine::Vector2Di PLAYER_SIZE = { 72, 96 };
		const float PLAYER_SPEED = 400.f;
		const float PLAYER_ANIMATION_FPS = 8.f;

		const std::string MUSIC_NAME = "theme";
		const float MUSIC_VOLUME = 40.f;
	}
}
