#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "Logger.h"

namespace XYZEngine
{
	AttackComponent::AttackComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
	}

	void AttackComponent::Update(float deltaTime)
	{
		if (cooldownLeft > 0.f)
		{
			cooldownLeft -= deltaTime;
		}

		if (autoTarget != nullptr)
		{
			TryAttack(autoTarget);
		}
	}

	void AttackComponent::Render()
	{
	}

	void AttackComponent::SetDamage(float newDamage)
	{
		if (newDamage <= 0.f)
		{
			LOG_WARNING("'" << gameObject->GetName() << "' got a non-positive attack damage " << newDamage);
		}
		damage = newDamage;
	}

	void AttackComponent::SetRange(float newRange)
	{
		range = newRange;
	}

	void AttackComponent::SetCooldown(float seconds)
	{
		cooldown = seconds;
	}

	bool AttackComponent::IsInRange(const HealthComponent* target) const
	{
		if (target == nullptr)
		{
			return false;
		}
		auto targetTransform = const_cast<HealthComponent*>(target)->GetGameObject()->GetComponent<TransformComponent>();
		const float distance = (targetTransform->GetWorldPosition() - transform->GetWorldPosition()).GetLength();
		return distance <= range;
	}

	bool AttackComponent::TryAttack(HealthComponent* target)
	{
		if (target == nullptr || target->IsDead() || !IsReady() || !IsInRange(target))
		{
			return false;
		}

		LOG_INFO("'" << gameObject->GetName() << "' attacks '" << target->GetGameObject()->GetName() << "' for " << damage);
		target->TakeDamage(damage, gameObject->GetName());
		cooldownLeft = cooldown;
		return true;
	}

	void AttackComponent::SetAutoTarget(HealthComponent* target)
	{
		autoTarget = target;
	}
}
