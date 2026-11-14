#include "Enemy.h"
#include "GameSettings.h"
#include <AttackComponent.h>
#include <AudioComponent.h>
#include <HealthComponent.h>
#include <Logger.h>
#include <ResourceSystem.h>
#include <RigidbodyComponent.h>
#include <SeekerComponent.h>
#include <SpriteColliderComponent.h>
#include <SpriteRendererComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Enemy::Enemy(const Vector2Df& position, GameObject* player, std::function<void()> onDeath)
	{
		gameObject = GameWorld::Instance()->CreateGameObject(Settings::ENEMY_OBJECT_NAME);
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared(Settings::ENEMY_TEXTURE));
		renderer->SetPixelSize(Settings::ENEMY_SIZE.x, Settings::ENEMY_SIZE.y);

		auto rigidbody = gameObject->AddComponent<RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		gameObject->AddComponent<SpriteColliderComponent>();

		auto seeker = gameObject->AddComponent<SeekerComponent>();
		seeker->SetTarget(player->GetComponent<TransformComponent>());
		seeker->SetSpeed(Settings::ENEMY_SPEED);
		seeker->SetDetectionRadius(Settings::ENEMY_DETECTION_RADIUS);
		seeker->SetStopDistance(Settings::ENEMY_STOP_DISTANCE);

		auto health = gameObject->AddComponent<HealthComponent>();
		health->SetMaxHealth(Settings::ENEMY_HEALTH);
		health->SetArmor(Settings::ENEMY_ARMOR);

		auto attack = gameObject->AddComponent<AttackComponent>();
		attack->SetDamage(Settings::ENEMY_DAMAGE);
		attack->SetRange(Settings::ENEMY_ATTACK_RANGE);
		attack->SetCooldown(Settings::ENEMY_ATTACK_COOLDOWN);
		attack->SetAutoTarget(player->GetComponent<HealthComponent>());

		auto deathSound = gameObject->AddComponent<AudioComponent>();
		deathSound->SetSound(ResourceSystem::Instance()->GetSound(Settings::DEATH_SOUND));

		// The object is removed at the end of the frame, so the attacker that killed it finishes its update safely
		GameObject* self = gameObject;
		health->SetOnDeath([self, deathSound, onDeath]() {
			deathSound->Play();
			LOG_INFO("Enemy defeated, removing it from the world");
			GameWorld::Instance()->DestroyGameObject(self);
			if (onDeath)
			{
				onDeath();
			}
		});

		LOG_INFO("Enemy created at " << position.x << ", " << position.y);
	}
}
