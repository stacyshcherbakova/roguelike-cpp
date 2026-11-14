#include "Player.h"
#include "GameSettings.h"
#include "PlayerCombatComponent.h"
#include <AttackComponent.h>
#include <AudioComponent.h>
#include <CameraComponent.h>
#include <InputComponent.h>
#include <Logger.h>
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
		gameObject = GameWorld::Instance()->CreateGameObject(Settings::PLAYER_OBJECT_NAME);
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

		auto health = gameObject->AddComponent<HealthComponent>();
		health->SetMaxHealth(Settings::PLAYER_HEALTH);
		health->SetArmor(Settings::PLAYER_ARMOR);

		auto attack = gameObject->AddComponent<AttackComponent>();
		attack->SetDamage(Settings::PLAYER_DAMAGE);
		attack->SetRange(Settings::PLAYER_ATTACK_RANGE);
		attack->SetCooldown(Settings::PLAYER_ATTACK_COOLDOWN);

		auto hitSound = gameObject->AddComponent<AudioComponent>();
		hitSound->SetSound(ResourceSystem::Instance()->GetSound(Settings::HIT_SOUND));

		gameObject->AddComponent<PlayerCombatComponent>();

		LOG_INFO("Player created at " << position.x << ", " << position.y
			<< " with " << Settings::PLAYER_HEALTH << " health and " << Settings::PLAYER_ARMOR << " armour");
	}

	HealthComponent* Player::GetHealth() const
	{
		return gameObject->GetComponent<HealthComponent>();
	}
}
