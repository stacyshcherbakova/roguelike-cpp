#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "Engine.h"
#include "Logger.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "RoguelikeGame.h"
#include "GameSettings.h"

using namespace XYZEngine;
using namespace XYZRoguelike;

namespace
{
	void LoadResources()
	{
		const std::string& root = Settings::RESOURCES_PATH;
		auto resources = ResourceSystem::Instance();

		resources->LoadTextureMap(Settings::PLAYER_TEXTURE_MAP, root + "TextureMaps/Player.png", { 48, 63 }, 9, false);
		resources->LoadTextureMap(Settings::FLOOR_TEXTURE_MAP, root + "TextureMaps/Floor.png", { 16, 16 }, 49, false);
		resources->LoadTextureMap(Settings::WALL_TEXTURE_MAP, root + "TextureMaps/Wall.png", { 16, 16 }, 48, false);
		resources->LoadTexture(Settings::ENEMY_TEXTURE, root + "Textures/Enemy.png", false);
		resources->LoadTexture(Settings::BOSS_TEXTURE, root + "Textures/Boss.png", false);
		resources->LoadTexture(Settings::POTION_TEXTURE, root + "Textures/Potion.png", false);
		resources->LoadFont(Settings::FONT_NAME, root + "Fonts/Roboto-Regular.ttf");
		resources->LoadTexture(Settings::DOOR_CLOSED_TEXTURE, root + "Textures/DoorClosed.png", false);
		resources->LoadTexture(Settings::DOOR_OPEN_TEXTURE, root + "Textures/DoorOpen.png", false);

		resources->RegisterMusic(Settings::MUSIC_NAME, root + "Music/theme.wav");
		resources->LoadSound(Settings::HIT_SOUND, root + "Sounds/AppleEat.wav");
		resources->LoadSound(Settings::DEATH_SOUND, root + "Sounds/Death.wav");

		// Optional decoration that is not shipped yet: the error is logged and the game goes on without it
		resources->LoadTexture("decor", root + "Textures/Decor.png", false);
	}
}

int main()
{
	LOG_INFO("=== " << Settings::GAME_NAME << " started ===");

	RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT), Settings::GAME_NAME));
	SpriteColliderComponent::SetDrawBounds(Settings::DRAW_COLLIDERS);

	try
	{
		LoadResources();
	}
	catch (const std::invalid_argument& error)
	{
		LOG_ERROR("Resource description is wrong: " << error.what());
	}

	RoguelikeGame game;
	try
	{
		game.Start();
	}
	catch (const std::exception& error)
	{
		LOG_ERROR("The game could not be started: " << error.what());
		return 1;
	}

	Engine::Instance()->Run();

	game.Stop();
	ResourceSystem::Instance()->Clear();
	LOG_INFO("=== " << Settings::GAME_NAME << " finished ===");
	return 0;
}
