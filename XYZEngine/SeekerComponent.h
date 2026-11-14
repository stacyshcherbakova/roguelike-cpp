#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace XYZEngine
{
	// Chases a target transform while it is inside the detection radius and stops when it leaves
	class SeekerComponent : public Component
	{
	public:
		SeekerComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(TransformComponent* newTarget);
		TransformComponent* GetTarget() const;

		void SetSpeed(float newSpeed);
		void SetDetectionRadius(float radius);
		// Distance at which the seeker stops pushing towards the target
		void SetStopDistance(float distance);

		bool IsChasing() const;
		float GetDistanceToTarget() const;
		// Last chase direction, normalized
		const Vector2Df& GetDirection() const;

	private:
		TransformComponent* transform = nullptr;
		TransformComponent* target = nullptr;

		float speed = 0.f;
		float detectionRadius = 0.f;
		float stopDistance = 0.f;
		bool isChasing = false;
		Vector2Df direction = { 0.f, 0.f };
	};
}
