#pragma once

#include "Component.h"
#include <SFML/Window.hpp>

namespace XYZEngine
{
	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;

		// True only on the frame the attack key went down
		bool IsAttackPressed() const;
		// True only on the frame the use-item key went down
		bool IsUsePressed() const;

	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;

		bool attackHeld = false;
		bool attackPressed = false;
		bool useHeld = false;
		bool usePressed = false;
	};
}
