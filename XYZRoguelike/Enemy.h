#pragma once

#include <functional>
#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Monster that waits until the player comes close, runs after him and bites when it reaches him
	class Enemy : public Entity
	{
	public:
		Enemy(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player, std::function<void()> onDeath = nullptr);
	};
}
