#include "Door.h"
#include "GameSettings.h"
#include <Logger.h>
#include <ResourceSystem.h>
#include <RigidbodyComponent.h>
#include <SpriteColliderComponent.h>
#include <SpriteRendererComponent.h>

using namespace XYZEngine;

namespace XYZRoguelike
{
	Door::Door(const Vector2Df& position)
	{
		gameObject = GameWorld::Instance()->CreateGameObject(Settings::DOOR_OBJECT_NAME);
		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared(Settings::DOOR_CLOSED_TEXTURE));
		renderer->SetPixelSize(Settings::TILE_SIZE, Settings::TILE_SIZE);

		auto rigidbody = gameObject->AddComponent<RigidbodyComponent>();
		rigidbody->SetKinematic(true);

		auto collider = gameObject->AddComponent<SpriteColliderComponent>();
		collider->SubscribeTriggerEnter([this, collider](Trigger trigger) {
			if (!isOpen || entered)
			{
				return;
			}
			auto other = trigger.GetOther(collider);
			if (other != nullptr && other->GetGameObject()->GetName() == Settings::PLAYER_OBJECT_NAME)
			{
				entered = true;
				LOG_INFO("The player walked through the door");
				if (onPlayerEnter)
				{
					onPlayerEnter();
				}
			}
		});
	}

	void Door::SetOpen(bool open)
	{
		isOpen = open;
		gameObject->GetComponent<SpriteRendererComponent>()->SetTexture(
			*ResourceSystem::Instance()->GetTextureShared(open ? Settings::DOOR_OPEN_TEXTURE : Settings::DOOR_CLOSED_TEXTURE));
		// A closed door pushes the player away like a wall, an open one only reports that he entered
		gameObject->GetComponent<SpriteColliderComponent>()->SetTrigger(open);
		LOG_INFO(open ? "The door is open" : "The door is closed");
	}

	void Door::SetOnPlayerEnter(std::function<void()> callback)
	{
		onPlayerEnter = std::move(callback);
	}
}
