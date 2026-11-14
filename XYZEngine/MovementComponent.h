#pragma once

#include "Component.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace XYZEngine
{
	// Moves the object by the input axes with a fixed speed
	class MovementComponent : public Component
	{
	public:
		MovementComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetSpeed(float newSpeed);
		float GetSpeed() const;

		bool IsMoving() const;
		// Last non-zero movement direction, normalized
		const Vector2Df& GetFacing() const;

	private:
		InputComponent* input = nullptr;
		TransformComponent* transform = nullptr;

		float speed = 0.f;
		bool isMoving = false;
		Vector2Df facing = { 1.f, 0.f };
	};
}
