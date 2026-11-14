#include "pch.h"
#include "KeyActionComponent.h"

namespace XYZEngine
{
	KeyActionComponent::KeyActionComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void KeyActionComponent::Update(float deltaTime)
	{
		if (key == sf::Keyboard::Unknown)
		{
			return;
		}

		const bool down = sf::Keyboard::isKeyPressed(key);
		if (down && !held && action)
		{
			action();
		}
		held = down;
	}

	void KeyActionComponent::Render()
	{
	}

	void KeyActionComponent::Bind(sf::Keyboard::Key newKey, std::function<void()> newAction)
	{
		key = newKey;
		action = std::move(newAction);
		held = sf::Keyboard::isKeyPressed(key);
	}
}
