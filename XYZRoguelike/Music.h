#pragma once

#include <string>
#include "Entity.h"

namespace XYZRoguelike
{
	// Background track that starts with the level and loops until the level is stopped
	class Music : public Entity
	{
	public:
		Music(const std::string& musicName, float volume);
	};
}
