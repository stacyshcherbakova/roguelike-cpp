#pragma once

#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Solid tile that nothing can walk through; it never moves itself
	class Wall : public Entity
	{
	public:
		Wall(const XYZEngine::Vector2Df& position, int tileIndex);
	};
}
