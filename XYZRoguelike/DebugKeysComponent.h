#pragma once

#include <functional>
#include <Component.h>

namespace XYZRoguelike
{
	// Developer shortcuts used while testing and at the demo: F2 opens the door of the current level
	class DebugKeysComponent : public XYZEngine::Component
	{
	public:
		DebugKeysComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetOnOpenDoor(std::function<void()> callback);

	private:
		bool openDoorHeld = false;
		std::function<void()> onOpenDoor;
	};
}
