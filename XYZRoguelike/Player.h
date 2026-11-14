#pragma once

#include "Entity.h"
#include "Vector.h"
#include <HealthComponent.h>
#include <InventoryComponent.h>

namespace XYZRoguelike
{
	class Player : public Entity
	{
	public:
		Player(const XYZEngine::Vector2Df& position);

		XYZEngine::HealthComponent* GetHealth() const;
		XYZEngine::InventoryComponent* GetInventory() const;
	};
}
