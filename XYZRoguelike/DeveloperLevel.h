#pragma once

#include <memory>
#include "Scene.h"
#include "Player.h"
#include "Music.h"

namespace XYZRoguelike
{
	class DeveloperLevel : public XYZEngine::Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;

	private:
		std::unique_ptr<Player> player;
		std::unique_ptr<Music> music;
	};
}
