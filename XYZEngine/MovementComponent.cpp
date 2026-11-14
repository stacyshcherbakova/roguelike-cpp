#include "pch.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "Logger.h"

namespace XYZEngine
{
	MovementComponent::MovementComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		transform = gameObject->GetComponent<TransformComponent>();

		if (input == nullptr)
		{
			LOG_WARNING("'" << gameObject->GetName() << "' has a MovementComponent but no InputComponent, it will not move");
		}
	}

	void MovementComponent::Update(float deltaTime)
	{
		if (input == nullptr)
		{
			return;
		}

		Vector2Df direction = { input->GetHorizontalAxis(), input->GetVerticalAxis() };
		const float length = direction.GetLength();
		isMoving = length > 0.f;
		if (!isMoving)
		{
			return;
		}

		direction = (1.f / length) * direction;
		facing = direction;
		transform->MoveBy(speed * deltaTime * direction);
	}

	void MovementComponent::Render()
	{
	}

	void MovementComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	float MovementComponent::GetSpeed() const
	{
		return speed;
	}

	bool MovementComponent::IsMoving() const
	{
		return isMoving;
	}

	const Vector2Df& MovementComponent::GetFacing() const
	{
		return facing;
	}
}
