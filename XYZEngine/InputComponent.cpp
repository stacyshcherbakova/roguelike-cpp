#include "pch.h"
#include "InputComponent.h"

namespace XYZEngine
{
	InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject) {}

	void InputComponent::Update(float deltaTime)
	{
		verticalAxis = 0.f;
		horizontalAxis = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			verticalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			verticalAxis -= 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			horizontalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			horizontalAxis -= 1.0f;
		}

		const bool attackDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		attackPressed = attackDown && !attackHeld;
		attackHeld = attackDown;

		const bool useDown = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		usePressed = useDown && !useHeld;
		useHeld = useDown;
	}
	void InputComponent::Render()
	{

	}

	float InputComponent::GetHorizontalAxis() const
	{
		return horizontalAxis;
	}
	float InputComponent::GetVerticalAxis() const
	{
		return verticalAxis;
	}

	bool InputComponent::IsAttackPressed() const
	{
		return attackPressed;
	}

	bool InputComponent::IsUsePressed() const
	{
		return usePressed;
	}
}
