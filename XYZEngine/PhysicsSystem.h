#pragma once

#include <map>
#include <set>
#include <utility>
#include <iostream>
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Vector.h"

namespace XYZEngine
{
	class PhysicsSystem
	{
	public:
		static PhysicsSystem* Instance();

		void Update();

		void Subscribe(ColliderComponent* collider);
		void Unsubscribe(ColliderComponent* collider);
	private:
		PhysicsSystem() {}
		~PhysicsSystem() {}

		PhysicsSystem(PhysicsSystem const&) = delete;
		PhysicsSystem& operator= (PhysicsSystem const&) = delete;

		// One pass over the pairs "moving body - static body" or "moving body - moving body"
		void ResolvePairs(bool againstStatic);
		// Pushes a moving body out of the static ones, the deepest overlap first
		void PushOutOfStatics(int i);
		Vector2Df GetPushOffset(int i, int j, const sf::FloatRect& intersection) const;
		void MoveCollider(ColliderComponent* collider, const Vector2Df& offset);
		void ReportContact(ColliderComponent* pushed, ColliderComponent* other);

		std::vector<ColliderComponent*> colliders;
		std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;
		// Pairs of bodies pushed apart on the previous update and on this one
		std::set<std::pair<ColliderComponent*, ColliderComponent*>> previousContacts;
		std::set<std::pair<ColliderComponent*, ColliderComponent*>> currentContacts;
	};
}