#include "Potion.h"
#include "GameSettings.h"
#include <AudioComponent.h>
#include <InventoryComponent.h>
#include <Logger.h>
#include <ResourceSystem.h>
#include <RigidbodyComponent.h>
#include <SpriteColliderComponent.h>
#include <SpriteRendererComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Potion::Potion(const Vector2Df& position)
	{
		gameObject = GameWorld::Instance()->CreateGameObject(Settings::POTION_OBJECT_NAME);
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared(Settings::POTION_TEXTURE));
		renderer->SetPixelSize(Settings::POTION_SIZE.x, Settings::POTION_SIZE.y);

		auto rigidbody = gameObject->AddComponent<RigidbodyComponent>();
		rigidbody->SetKinematic(true);

		auto collider = gameObject->AddComponent<SpriteColliderComponent>();
		collider->SetTrigger(true);

		auto pickupSound = gameObject->AddComponent<AudioComponent>();
		pickupSound->SetSound(ResourceSystem::Instance()->GetSound(Settings::HIT_SOUND));

		GameObject* self = gameObject;
		collider->SubscribeTriggerEnter([self, collider, pickupSound](Trigger trigger) {
			auto other = trigger.GetOther(collider);
			if (other == nullptr || other->GetGameObject()->GetName() != Settings::PLAYER_OBJECT_NAME)
			{
				return;
			}
			auto inventory = other->GetGameObject()->GetComponent<InventoryComponent>();
			if (inventory == nullptr)
			{
				LOG_WARNING("The player has no inventory, the potion stays on the floor");
				return;
			}
			inventory->Add(Settings::POTION_ITEM);
			pickupSound->Play();
			GameWorld::Instance()->DestroyGameObject(self);
		});
	}
}
