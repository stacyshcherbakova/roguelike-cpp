#pragma once

#include "GameObject.h"
#include "GameWorld.h"
#include "TransformComponent.h"

namespace XYZRoguelike
{
	// Base for the game-side containers: each one owns a GameObject assembled from engine components
	class Entity
	{
	public:
		virtual ~Entity() = default;

		XYZEngine::GameObject* GetGameObject() const { return gameObject; }
		XYZEngine::TransformComponent* GetTransform() const { return gameObject->GetComponent<XYZEngine::TransformComponent>(); }

	protected:
		XYZEngine::GameObject* gameObject = nullptr;
	};
}
