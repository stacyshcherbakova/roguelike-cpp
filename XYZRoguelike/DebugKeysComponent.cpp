#include "DebugKeysComponent.h"
#include <Logger.h>
#include <SFML/Window/Keyboard.hpp>

using namespace XYZEngine;

namespace XYZRoguelike
{
	DebugKeysComponent::DebugKeysComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void DebugKeysComponent::Update(float deltaTime)
	{
		const bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::F2);
		if (down && !openDoorHeld && onOpenDoor)
		{
			LOG_WARNING("Debug key: the door is forced open");
			onOpenDoor();
		}
		openDoorHeld = down;
	}

	void DebugKeysComponent::Render()
	{
	}

	void DebugKeysComponent::SetOnOpenDoor(std::function<void()> callback)
	{
		onOpenDoor = std::move(callback);
	}
}
