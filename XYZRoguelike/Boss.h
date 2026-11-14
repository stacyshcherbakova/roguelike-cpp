#pragma once

#include <functional>
#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Big monster guarding the door: chases like an enemy, hits harder and charges across the room
	class Boss : public Entity
	{
	public:
		Boss(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player, float healthScale, std::function<void()> onDeath = nullptr);
	};
}
