#pragma once

#include <Component.h>
#include <AttackComponent.h>
#include <AudioComponent.h>
#include <InputComponent.h>

namespace XYZRoguelike
{
	// Game-side component: on the attack key hits the nearest enemy within the player's reach
	class PlayerCombatComponent : public XYZEngine::Component
	{
	public:
		PlayerCombatComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

	private:
		XYZEngine::InputComponent* input = nullptr;
		XYZEngine::AttackComponent* attack = nullptr;
		XYZEngine::AudioComponent* hitSound = nullptr;
	};
}
