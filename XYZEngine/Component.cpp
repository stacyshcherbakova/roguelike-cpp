#include "pch.h"
#include "Component.h"

#include <cassert>

namespace XYZEngine
{
	Component::Component(GameObject* gameObject) : gameObject(gameObject)
	{
		assert(gameObject != nullptr && "A component must belong to a game object");
	}
	Component::~Component()
	{
	}
	GameObject* Component::GetGameObject()
	{
		return gameObject;
	}
}
