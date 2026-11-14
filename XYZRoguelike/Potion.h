#pragma once

#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Healing potion lying on the floor; the player picks it up by walking over it
	class Potion : public Entity
	{
	public:
		Potion(const XYZEngine::Vector2Df& position);
	};
}
