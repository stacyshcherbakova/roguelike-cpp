#include "Enemy.h"
#include "GameSettings.h"
#include <ResourceSystem.h>
#include <RigidbodyComponent.h>
#include <SeekerComponent.h>
#include <SpriteColliderComponent.h>
#include <SpriteRendererComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Enemy::Enemy(const Vector2Df& position, TransformComponent* target)
	{
		gameObject = GameWorld::Instance()->CreateGameObject("Enemy");
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared(Settings::ENEMY_TEXTURE));
		renderer->SetPixelSize(Settings::ENEMY_SIZE.x, Settings::ENEMY_SIZE.y);

		auto rigidbody = gameObject->AddComponent<RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		gameObject->AddComponent<SpriteColliderComponent>();

		auto seeker = gameObject->AddComponent<SeekerComponent>();
		seeker->SetTarget(target);
		seeker->SetSpeed(Settings::ENEMY_SPEED);
		seeker->SetDetectionRadius(Settings::ENEMY_DETECTION_RADIUS);
		seeker->SetStopDistance(Settings::ENEMY_STOP_DISTANCE);
	}
}
