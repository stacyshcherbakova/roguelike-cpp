#include "Boss.h"
#include "ChargeComponent.h"
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
	Boss::Boss(const Vector2Df& position, GameObject* player, float healthScale, std::function<void()> onDeath)
	{
		gameObject = GameWorld::Instance()->CreateGameObject(Settings::BOSS_OBJECT_NAME);
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared(Settings::BOSS_TEXTURE));
		renderer->SetPixelSize(Settings::BOSS_SIZE.x, Settings::BOSS_SIZE.y);

		auto rigidbody = gameObject->AddComponent<RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		gameObject->AddComponent<SpriteColliderComponent>();

		auto playerTransform = player->GetComponent<TransformComponent>();

		auto seeker = gameObject->AddComponent<SeekerComponent>();
		seeker->SetTarget(playerTransform);
		seeker->SetSpeed(Settings::BOSS_SPEED);
		seeker->SetDetectionRadius(Settings::BOSS_DETECTION_RADIUS);
		seeker->SetStopDistance(Settings::BOSS_STOP_DISTANCE);

		auto charge = gameObject->AddComponent<ChargeComponent>();
		charge->SetTarget(playerTransform);
		charge->SetInterval(Settings::BOSS_CHARGE_INTERVAL);
		charge->SetDuration(Settings::BOSS_CHARGE_DURATION);
		charge->SetSpeed(Settings::BOSS_CHARGE_SPEED);
		charge->SetTriggerDistance(Settings::BOSS_CHARGE_DISTANCE);

		auto health = gameObject->AddComponent<HealthComponent>();
		health->SetMaxHealth(Settings::BOSS_HEALTH * healthScale);
		health->SetArmor(Settings::BOSS_ARMOR);

		auto attack = gameObject->AddComponent<AttackComponent>();
		attack->SetDamage(Settings::BOSS_DAMAGE);
		attack->SetRange(Settings::BOSS_ATTACK_RANGE);
		attack->SetCooldown(Settings::BOSS_ATTACK_COOLDOWN);
		attack->SetAutoTarget(player->GetComponent<HealthComponent>());

		auto deathSound = gameObject->AddComponent<AudioComponent>();
		deathSound->SetSound(ResourceSystem::Instance()->GetSound(Settings::DEATH_SOUND));

		GameObject* self = gameObject;
		health->SetOnDeath([self, deathSound, onDeath]() {
			deathSound->Play();
			LOG_INFO("Boss defeated, removing it from the world");
			GameWorld::Instance()->DestroyGameObject(self);
			if (onDeath)
			{
				onDeath();
			}
		});

		LOG_INFO("Boss created at " << position.x << ", " << position.y << " with " << health->GetMaxHealth() << " health");
	}
}
