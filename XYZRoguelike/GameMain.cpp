#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "GameSettings.h"

using namespace XYZEngine;
using namespace XYZRoguelike;

namespace
{
	void LoadResources()
	{
		const std::string& root = Settings::RESOURCES_PATH;
		ResourceSystem::Instance()->LoadTextureMap(Settings::PLAYER_TEXTURE_MAP, root + "TextureMaps/Player.png", { 48, 63 }, 9, false);
		ResourceSystem::Instance()->RegisterMusic(Settings::MUSIC_NAME, root + "Music/theme.wav");
	}
}

int main()
{
	RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT), Settings::GAME_NAME));

	LoadResources();

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	Engine::Instance()->Run();

	developerLevel->Stop();
	return 0;
}
