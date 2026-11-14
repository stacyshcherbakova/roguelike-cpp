#pragma once

#include <functional>
#include <string>
#include "Entity.h"
#include <ScreenTextComponent.h>

namespace XYZRoguelike
{
	// Two lines of text in the corner of the screen. The first line is rebuilt every frame
	// by the provider function, the second one is a fixed hint.
	class Hud : public Entity
	{
	public:
		Hud(std::function<std::string()> statusProvider, const std::string& hint);
	};

	// Keeps the status text of the HUD up to date
	class HudComponent : public XYZEngine::Component
	{
	public:
		HudComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void Initialize(XYZEngine::ScreenTextComponent* statusText, std::function<std::string()> provider);

	private:
		XYZEngine::ScreenTextComponent* statusText = nullptr;
		std::function<std::string()> statusProvider;
	};
}
