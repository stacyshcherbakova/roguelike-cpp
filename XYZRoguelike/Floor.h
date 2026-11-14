#pragma once

#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Decorative tile under the walkable area, no physics
	class Floor : public Entity
	{
	public:
		Floor(const XYZEngine::Vector2Df& position, int tileIndex);
	};
}
