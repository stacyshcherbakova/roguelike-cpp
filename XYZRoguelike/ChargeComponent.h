#pragma once

#include <Component.h>
#include <TransformComponent.h>
#include <Vector.h>

namespace XYZRoguelike
{
	// Boss ability: every few seconds the boss dashes towards where the target was standing
	class ChargeComponent : public XYZEngine::Component
	{
	public:
		ChargeComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(XYZEngine::TransformComponent* newTarget);
		void SetInterval(float seconds);
		void SetDuration(float seconds);
		void SetSpeed(float pixelsPerSecond);
		void SetTriggerDistance(float distance);

		bool IsCharging() const { return chargeLeft > 0.f; }

	private:
		XYZEngine::TransformComponent* transform = nullptr;
		XYZEngine::TransformComponent* target = nullptr;

		float interval = 4.f;
		float duration = 0.5f;
		float speed = 800.f;
		float triggerDistance = 650.f;

		float cooldownLeft = 2.f;
		float chargeLeft = 0.f;
		XYZEngine::Vector2Df direction = { 0.f, 0.f };
	};
}
