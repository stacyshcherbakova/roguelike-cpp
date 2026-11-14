#pragma once

#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	class Player : public Entity
	{
	public:
		Player(const XYZEngine::Vector2Df& position);
	};
}
