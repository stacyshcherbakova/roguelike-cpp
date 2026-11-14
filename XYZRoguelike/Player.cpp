#include "Player.h"
#include "GameSettings.h"
#include <CameraComponent.h>
#include <InputComponent.h>
#include <MovementComponent.h>
#include <RenderSystem.h>
#include <ResourceSystem.h>
#include <RigidbodyComponent.h>
#include <SpriteColliderComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <SpriteRendererComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Player::Player(const Vector2Df& position)
	{
		gameObject = GameWorld::Instance()->CreateGameObject("Player");
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureMapElementShared(Settings::PLAYER_TEXTURE_MAP, 0));
		renderer->SetPixelSize(Settings::PLAYER_SIZE.x, Settings::PLAYER_SIZE.y);

		auto camera = gameObject->AddComponent<CameraComponent>();
		camera->SetWindow(&RenderSystem::Instance()->GetMainWindow());
		camera->SetBaseResolution(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT);

		gameObject->AddComponent<InputComponent>();

		auto movement = gameObject->AddComponent<MovementComponent>();
		movement->SetSpeed(Settings::PLAYER_SPEED);

		auto rigidbody = gameObject->AddComponent<RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		gameObject->AddComponent<SpriteColliderComponent>();

		auto animation = gameObject->AddComponent<SpriteMovementAnimationComponent>();
		animation->Initialize(Settings::PLAYER_TEXTURE_MAP, Settings::PLAYER_ANIMATION_FPS);
	}
}
