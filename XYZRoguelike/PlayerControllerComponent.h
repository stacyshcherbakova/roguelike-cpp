#pragma once

#include <Component.h>
#include <AttackComponent.h>
#include <AudioComponent.h>
#include <HealthComponent.h>
#include <InputComponent.h>
#include <InventoryComponent.h>

namespace XYZRoguelike
{
	// Game-side component: turns the player's key presses into attacks and item use
	class PlayerControllerComponent : public XYZEngine::Component
	{
	public:
		PlayerControllerComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

	private:
		void Attack();
		void UsePotion();

		XYZEngine::InputComponent* input = nullptr;
		XYZEngine::AttackComponent* attack = nullptr;
		XYZEngine::HealthComponent* health = nullptr;
		XYZEngine::InventoryComponent* inventory = nullptr;
		XYZEngine::AudioComponent* hitSound = nullptr;
	};
}
