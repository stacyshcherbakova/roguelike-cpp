#include "Hud.h"
#include "GameSettings.h"
#include <ResourceSystem.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Hud::Hud(std::function<std::string()> statusProvider, const std::string& hint)
	{
		gameObject = GameWorld::Instance()->CreateGameObject(Settings::HUD_OBJECT_NAME);
		const sf::Font* font = ResourceSystem::Instance()->GetFont(Settings::FONT_NAME);

		auto status = gameObject->AddComponent<ScreenTextComponent>();
		status->SetFont(font);
		status->SetCharacterSize(Settings::HUD_TEXT_SIZE);
		status->SetScreenPosition(Settings::HUD_MARGIN, Settings::HUD_MARGIN);

		auto hintText = gameObject->AddComponent<ScreenTextComponent>();
		hintText->SetFont(font);
		hintText->SetCharacterSize(Settings::HUD_HINT_SIZE);
		hintText->SetColor(sf::Color(220, 220, 220));
		hintText->SetAnchor(0.f, 1.f);
		hintText->SetScreenPosition(Settings::HUD_MARGIN, -Settings::HUD_MARGIN);
		hintText->SetString(hint);

		auto updater = gameObject->AddComponent<HudComponent>();
		updater->Initialize(status, std::move(statusProvider));
	}

	HudComponent::HudComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void HudComponent::Initialize(ScreenTextComponent* text, std::function<std::string()> provider)
	{
		statusText = text;
		statusProvider = std::move(provider);
	}

	void HudComponent::Update(float deltaTime)
	{
		if (statusText != nullptr && statusProvider)
		{
			statusText->SetString(statusProvider());
		}
	}

	void HudComponent::Render()
	{
	}
}
