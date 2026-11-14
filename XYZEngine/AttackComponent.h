#pragma once

#include "Component.h"
#include "HealthComponent.h"
#include "TransformComponent.h"

namespace XYZEngine
{
	// Melee attack with range and cooldown. Can be triggered by the game or attack a target on its own.
	class AttackComponent : public Component
	{
	public:
		AttackComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetDamage(float newDamage);
		void SetRange(float newRange);
		void SetCooldown(float seconds);

		float GetDamage() const { return damage; }
		float GetRange() const { return range; }
		bool IsReady() const { return cooldownLeft <= 0.f; }

		bool IsInRange(const HealthComponent* target) const;
		// Deals damage if the target is alive, in range and the cooldown has passed
		bool TryAttack(HealthComponent* target);

		// Attacks this target automatically whenever it is possible
		void SetAutoTarget(HealthComponent* target);

	private:
		TransformComponent* transform = nullptr;
		HealthComponent* autoTarget = nullptr;

		float damage = 10.f;
		float range = 100.f;
		float cooldown = 1.f;
		float cooldownLeft = 0.f;
	};
}
