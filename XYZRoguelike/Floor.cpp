#include "Floor.h"
#include "GameSettings.h"
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Floor::Floor(const Vector2Df& position, int tileIndex)
	{
		gameObject = GameWorld::Instance()->CreateGameObject("Floor");
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureMapElementShared(Settings::FLOOR_TEXTURE_MAP, tileIndex));
		renderer->SetPixelSize(Settings::TILE_SIZE, Settings::TILE_SIZE);
	}
}
