#include "RoguelikeGame.h"
#include "GameSettings.h"
#include <GameWorld.h>
#include <KeyActionComponent.h>
#include <Logger.h>
#include <sstream>

using namespace XYZEngine;

namespace XYZRoguelike
{
	RoguelikeGame::RoguelikeGame()
	{
		levels = {
			{ "Cellar", 12, 9, 3, 0, 14, 0.6f, 2 },
			{ "Catacombs", 16, 11, 5, 8, 26, 1.f, 3 },
			{ "Throne hall", 20, 13, 7, 40, 38, 1.5f, 4 },
		};
	}

	void RoguelikeGame::Start()
	{
		deaths = 0;
		StartLevel(0);
	}

	void RoguelikeGame::Stop()
	{
		victoryScreen.reset();
		if (level)
		{
			level->Stop();
			level.reset();
		}
	}

	void RoguelikeGame::StartLevel(int index)
	{
		victoryScreen.reset();
		if (level)
		{
			level->Stop();
		}
		currentLevel = index;
		level = std::make_unique<GameLevel>(levels[index],
			[this]() { OnLevelCompleted(); },
			[this]() { OnPlayerDied(); },
			[this]() { return BuildHudStatus(); });
		level->Start();
		LOG_INFO("Level " << (index + 1) << " of " << levels.size() << " is running");
	}

	void RoguelikeGame::ShowVictory()
	{
		if (level)
		{
			level->Stop();
			level.reset();
		}
		GameWorld::Instance()->Clear();

		std::ostringstream text;
		text << "YOU WON!\nAll " << levels.size() << " locations are cleared";
		if (deaths > 0)
		{
			text << " after " << deaths << (deaths == 1 ? " death" : " deaths");
		}
		const std::string message = text.str();
		victoryScreen = std::make_unique<Hud>([message]() { return message; }, "Press R to play again");

		auto restartKey = victoryScreen->GetGameObject()->AddComponent<KeyActionComponent>();
		restartKey->Bind(sf::Keyboard::R, [this]() {
			GameWorld::Instance()->RunLater([this]() { Start(); });
		});
		LOG_INFO("Victory screen shown");
	}

	void RoguelikeGame::OnLevelCompleted()
	{
		// Scene changes are deferred to the end of the frame: the callback comes from inside a component update
		const int next = currentLevel + 1;
		if (next < (int)levels.size())
		{
			LOG_INFO("Level '" << levels[currentLevel].name << "' completed, loading the next one");
			GameWorld::Instance()->RunLater([this, next]() { StartLevel(next); });
		}
		else
		{
			LOG_INFO("The last level is completed");
			GameWorld::Instance()->RunLater([this]() { ShowVictory(); });
		}
	}

	void RoguelikeGame::OnPlayerDied()
	{
		deaths++;
		LOG_WARNING("Level '" << levels[currentLevel].name << "' restarts because the player died (death " << deaths << ")");
		GameWorld::Instance()->RunLater([this]() { level->Restart(); });
	}

	std::string RoguelikeGame::BuildHudStatus() const
	{
		if (!level || level->GetPlayer() == nullptr)
		{
			return std::string();
		}

		auto health = level->GetPlayer()->GetHealth();
		auto inventory = level->GetPlayer()->GetInventory();

		std::ostringstream status;
		status << "HP " << (int)health->GetHealth() << "/" << (int)health->GetMaxHealth()
			<< "   Armour " << (int)health->GetArmor()
			<< "   Potions " << inventory->Count(Settings::POTION_ITEM)
			<< "   Level " << (currentLevel + 1) << "/" << levels.size() << ": " << level->GetDefinition().name
			<< "   Enemies " << level->GetAliveEnemies()
			<< "   Boss " << (level->IsBossAlive() ? "alive" : "defeated");
		return status.str();
	}
}
