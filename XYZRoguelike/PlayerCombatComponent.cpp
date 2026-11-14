#include "PlayerCombatComponent.h"
#include "GameSettings.h"
#include <GameObject.h>
#include <GameWorld.h>
#include <HealthComponent.h>
#include <Logger.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	PlayerCombatComponent::PlayerCombatComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		attack = gameObject->GetComponent<AttackComponent>();
		hitSound = gameObject->GetComponent<AudioComponent>();

		if (input == nullptr || attack == nullptr)
		{
			LOG_ERROR("'" << gameObject->GetName() << "' needs InputComponent and AttackComponent to fight");
		}
	}

	void PlayerCombatComponent::Update(float deltaTime)
	{
		if (input == nullptr || attack == nullptr || !input->IsAttackPressed())
		{
			return;
		}

		if (!attack->IsReady())
		{
			LOG_DEBUG("Attack key pressed while the attack is still on cooldown");
			return;
		}

		// Pick the closest living enemy inside the attack range
		auto ownTransform = gameObject->GetComponent<TransformComponent>();
		HealthComponent* bestTarget = nullptr;
		float bestDistance = 0.f;
		for (auto enemy : GameWorld::Instance()->FindGameObjectsByName(Settings::ENEMY_OBJECT_NAME))
		{
			auto health = enemy->GetComponent<HealthComponent>();
			if (health == nullptr || health->IsDead() || !attack->IsInRange(health))
			{
				continue;
			}
			const float distance = (enemy->GetComponent<TransformComponent>()->GetWorldPosition() - ownTransform->GetWorldPosition()).GetLength();
			if (bestTarget == nullptr || distance < bestDistance)
			{
				bestTarget = health;
				bestDistance = distance;
			}
		}

		if (bestTarget == nullptr)
		{
			LOG_DEBUG("Player swings but no enemy is within " << attack->GetRange() << " px");
			return;
		}

		if (attack->TryAttack(bestTarget) && hitSound != nullptr)
		{
			hitSound->Play();
		}
	}

	void PlayerCombatComponent::Render()
	{
	}
}
