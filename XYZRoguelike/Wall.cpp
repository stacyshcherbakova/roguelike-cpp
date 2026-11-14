#include "Wall.h"
#include "GameSettings.h"
#include <ResourceSystem.h>
#include <RigidbodyComponent.h>
#include <SpriteColliderComponent.h>
#include <SpriteRendererComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Wall::Wall(const Vector2Df& position, int tileIndex)
	{
		gameObject = GameWorld::Instance()->CreateGameObject("Wall");
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureMapElementShared(Settings::WALL_TEXTURE_MAP, tileIndex));
		renderer->SetPixelSize(Settings::TILE_SIZE, Settings::TILE_SIZE);

		// Kinematic bodies are never pushed by the physics system, so walls stay in place
		auto rigidbody = gameObject->AddComponent<RigidbodyComponent>();
		rigidbody->SetKinematic(true);

		gameObject->AddComponent<SpriteColliderComponent>();
	}
}
