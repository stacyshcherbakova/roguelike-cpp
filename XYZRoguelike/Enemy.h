#pragma once

#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Monster that waits until the player comes close and then runs after him
	class Enemy : public Entity
	{
	public:
		Enemy(const XYZEngine::Vector2Df& position, XYZEngine::TransformComponent* target);
	};
}
