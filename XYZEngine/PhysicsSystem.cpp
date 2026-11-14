#include "pch.h"
#include "PhysicsSystem.h"
#include "Logger.h"

#include <cassert>

namespace XYZEngine
{
	PhysicsSystem* PhysicsSystem::Instance()
	{
		static PhysicsSystem physicsSystem;
		return &physicsSystem;
	}

	float PhysicsSystem::GetFixedDeltaTime() const
	{
		return fixedDeltaTime;
	}

	void PhysicsSystem::Update()
	{
		// Moving bodies are pushed apart first and out of the static ones last:
		// whatever the monsters do to each other, nobody finishes a step inside a wall
		ResolvePairs(false);
		ResolvePairs(true);

		for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair; triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
		{
			++nextTriggeredPair;
			if (!triggeredPair->first->bounds.intersects(triggeredPair->second->bounds))
			{
				Trigger trigger(triggeredPair->first, triggeredPair->second);
				triggeredPair->first->OnTriggerExit(trigger);
				triggeredPair->second->OnTriggerExit(trigger);

				triggersEnteredPair.erase(triggeredPair);
			}
		}
	}

	void PhysicsSystem::ResolvePairs(bool againstStatic)
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			auto body = colliders[i]->GetGameObject()->GetComponent<RigidbodyComponent>();
			if (body == nullptr)
			{
				if (!againstStatic)
				{
					LOG_WARNING("Collider of '" << colliders[i]->GetGameObject()->GetName() << "' has no RigidbodyComponent and is skipped");
				}
				continue;
			}
			if (body->GetKinematic())
			{
				continue;
			}

			for (int j = 0; j < colliders.size(); j++)
			{
				if (j == i)
				{
					continue;
				}

				auto otherBody = colliders[j]->GetGameObject()->GetComponent<RigidbodyComponent>();
				const bool isOtherStatic = otherBody == nullptr || otherBody->GetKinematic();
				if (isOtherStatic != againstStatic)
				{
					continue;
				}

				sf::FloatRect intersection;
				if (colliders[i]->bounds.intersects(colliders[j]->bounds, intersection))
				{
					if (colliders[i]->isTrigger != colliders[j]->isTrigger)
					{
						if (triggersEnteredPair.find(colliders[i]) == triggersEnteredPair.end() && triggersEnteredPair.find(colliders[j]) == triggersEnteredPair.end())
						{
							Trigger trigger(colliders[i], colliders[j]);
							colliders[i]->OnTriggerEnter(trigger);
							colliders[j]->OnTriggerEnter(trigger);

							triggersEnteredPair.emplace(colliders[i], colliders[j]);
							LOG_DEBUG("Trigger enter: '" << colliders[i]->GetGameObject()->GetName() << "' and '" << colliders[j]->GetGameObject()->GetName() << "'");
						}
					}
					else if (!colliders[i]->isTrigger)
					{
						// Push along the axis of the smaller overlap, away from the centre of the other body.
						// Comparing centres keeps the direction right however deep the overlap is;
						// two bodies with the same centre are split by their order in the list.
						const sf::FloatRect& aBounds = colliders[i]->bounds;
						const sf::FloatRect& bBounds = colliders[j]->bounds;
						Vector2Df offset;

						if (intersection.width > intersection.height)
						{
							const float aCentre = aBounds.top + 0.5f * aBounds.height;
							const float bCentre = bBounds.top + 0.5f * bBounds.height;
							const bool isBefore = aCentre < bCentre || (aCentre == bCentre && i < j);
							offset.y = isBefore ? -intersection.height : intersection.height;
						}
						else
						{
							const float aCentre = aBounds.left + 0.5f * aBounds.width;
							const float bCentre = bBounds.left + 0.5f * bBounds.width;
							const bool isBefore = aCentre < bCentre || (aCentre == bCentre && i < j);
							offset.x = isBefore ? -intersection.width : intersection.width;
						}

						if (isOtherStatic)
						{
							MoveCollider(colliders[i], offset);
						}
						else
						{
							// Two moving bodies share the push, so the pair is already apart when it is met in the other order
							MoveCollider(colliders[i], 0.5f * offset);
							MoveCollider(colliders[j], -0.5f * offset);
						}

						LOG_DEBUG("Collision: '" << colliders[i]->GetGameObject()->GetName() << "' pushed out of '" << colliders[j]->GetGameObject()->GetName() << "'");

						Collision collision(colliders[i], colliders[j], intersection);
						colliders[i]->OnCollision(collision);
						colliders[j]->OnCollision(collision);
					}
				}
			}
		}
	}

	void PhysicsSystem::MoveCollider(ColliderComponent* collider, const Vector2Df& offset)
	{
		collider->GetGameObject()->GetComponent<TransformComponent>()->MoveBy(offset);
		// The cached bounds follow the transform at once, so the next pair of this step sees the new position
		collider->bounds.left += offset.x;
		collider->bounds.top += offset.y;
	}

	void PhysicsSystem::Subscribe(ColliderComponent* collider)
	{
		assert(collider != nullptr && "Cannot subscribe a null collider");
		colliders.push_back(collider);
		LOG_DEBUG("Collider subscribed: '" << collider->GetGameObject()->GetName() << "'");
	}
	void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
	{
		colliders.erase(std::remove_if(colliders.begin(), colliders.end(), [collider](ColliderComponent* obj) { return obj == collider; }), colliders.end());

		for (auto pair = triggersEnteredPair.begin(); pair != triggersEnteredPair.end();)
		{
			if (pair->first == collider || pair->second == collider)
			{
				pair = triggersEnteredPair.erase(pair);
			}
			else
			{
				++pair;
			}
		}
	}
}
