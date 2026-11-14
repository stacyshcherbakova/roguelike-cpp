#include "pch.h"
#include "SeekerComponent.h"
#include "GameObject.h"

namespace XYZEngine
{
	SeekerComponent::SeekerComponent(GameObject* gameObject) : Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
	}

	void SeekerComponent::Update(float deltaTime)
	{
		if (target == nullptr)
		{
			isChasing = false;
			return;
		}

		Vector2Df delta = target->GetWorldPosition() - transform->GetWorldPosition();
		const float distance = delta.GetLength();

		isChasing = distance <= detectionRadius;
		if (!isChasing || distance <= stopDistance || distance <= 0.f)
		{
			return;
		}

		direction = (1.f / distance) * delta;
		float step = speed * deltaTime;
		if (step > distance - stopDistance)
		{
			step = distance - stopDistance;
		}
		transform->MoveBy(step * direction);
	}

	void SeekerComponent::Render()
	{
	}

	void SeekerComponent::SetTarget(TransformComponent* newTarget)
	{
		target = newTarget;
	}

	TransformComponent* SeekerComponent::GetTarget() const
	{
		return target;
	}

	void SeekerComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	void SeekerComponent::SetDetectionRadius(float radius)
	{
		detectionRadius = radius;
	}

	void SeekerComponent::SetStopDistance(float distance)
	{
		stopDistance = distance;
	}

	bool SeekerComponent::IsChasing() const
	{
		return isChasing;
	}

	float SeekerComponent::GetDistanceToTarget() const
	{
		if (target == nullptr)
		{
			return 0.f;
		}
		return (target->GetWorldPosition() - transform->GetWorldPosition()).GetLength();
	}

	const Vector2Df& SeekerComponent::GetDirection() const
	{
		return direction;
	}
}
