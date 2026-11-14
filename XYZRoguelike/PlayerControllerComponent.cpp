#include "PlayerControllerComponent.h"
#include "GameSettings.h"
#include <GameObject.h>
#include <GameWorld.h>
#include <Logger.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	PlayerControllerComponent::PlayerControllerComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		attack = gameObject->GetComponent<AttackComponent>();
		health = gameObject->GetComponent<HealthComponent>();
		inventory = gameObject->GetComponent<InventoryComponent>();
		hitSound = gameObject->GetComponent<AudioComponent>();

		if (input == nullptr || attack == nullptr || health == nullptr || inventory == nullptr)
		{
			LOG_ERROR("'" << gameObject->GetName() << "' needs Input, Attack, Health and Inventory components to be controlled");
		}
	}

	void PlayerControllerComponent::Update(float deltaTime)
	{
		if (input == nullptr)
		{
			return;
		}
		if (input->IsAttackPressed())
		{
			Attack();
		}
		if (input->IsUsePressed())
		{
			UsePotion();
		}
	}

	void PlayerControllerComponent::Attack()
	{
		if (attack == nullptr)
		{
			return;
		}
		if (!attack->IsReady())
		{
			LOG_DEBUG("Attack key pressed while the attack is still on cooldown");
			return;
		}

		// Pick the closest living monster inside the attack range
		auto ownTransform = gameObject->GetComponent<TransformComponent>();
		HealthComponent* bestTarget = nullptr;
		float bestDistance = 0.f;
		for (const auto& name : { Settings::ENEMY_OBJECT_NAME, Settings::BOSS_OBJECT_NAME })
		{
			for (auto monster : GameWorld::Instance()->FindGameObjectsByName(name))
			{
				auto monsterHealth = monster->GetComponent<HealthComponent>();
				if (monsterHealth == nullptr || monsterHealth->IsDead() || !attack->IsInRange(monsterHealth))
				{
					continue;
				}
				const float distance = (monster->GetComponent<TransformComponent>()->GetWorldPosition() - ownTransform->GetWorldPosition()).GetLength();
				if (bestTarget == nullptr || distance < bestDistance)
				{
					bestTarget = monsterHealth;
					bestDistance = distance;
				}
			}
		}

		if (bestTarget == nullptr)
		{
			LOG_DEBUG("Player swings but nothing is within " << attack->GetRange() << " px");
			return;
		}

		if (attack->TryAttack(bestTarget) && hitSound != nullptr)
		{
			hitSound->Play();
		}
	}

	void PlayerControllerComponent::UsePotion()
	{
		if (inventory == nullptr || health == nullptr)
		{
			return;
		}
		if (health->GetHealth() >= health->GetMaxHealth())
		{
			LOG_INFO("Health is already full, the potion is kept");
			return;
		}
		if (inventory->Use(Settings::POTION_ITEM))
		{
			health->Heal(Settings::POTION_HEAL);
		}
	}

	void PlayerControllerComponent::Render()
	{
	}
}
