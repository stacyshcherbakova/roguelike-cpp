#include "ChargeComponent.h"
#include <GameObject.h>
#include <Logger.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	ChargeComponent::ChargeComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
	}

	void ChargeComponent::Update(float deltaTime)
	{
		if (chargeLeft > 0.f)
		{
			chargeLeft -= deltaTime;
			transform->MoveBy(speed * deltaTime * direction);
			return;
		}

		if (target == nullptr)
		{
			return;
		}

		cooldownLeft -= deltaTime;
		if (cooldownLeft > 0.f)
		{
			return;
		}

		Vector2Df delta = target->GetWorldPosition() - transform->GetWorldPosition();
		const float distance = delta.GetLength();
		if (distance > triggerDistance || distance <= 0.f)
		{
			return;
		}

		direction = (1.f / distance) * delta;
		chargeLeft = duration;
		cooldownLeft = interval;
		LOG_INFO("'" << gameObject->GetName() << "' charges at '" << target->GetGameObject()->GetName() << "' from " << (int)distance << " px");
	}

	void ChargeComponent::Render()
	{
	}

	void ChargeComponent::SetTarget(TransformComponent* newTarget)
	{
		target = newTarget;
	}

	void ChargeComponent::SetInterval(float seconds)
	{
		interval = seconds;
	}

	void ChargeComponent::SetDuration(float seconds)
	{
		duration = seconds;
	}

	void ChargeComponent::SetSpeed(float pixelsPerSecond)
	{
		speed = pixelsPerSecond;
	}

	void ChargeComponent::SetTriggerDistance(float distance)
	{
		triggerDistance = distance;
	}
}
