#pragma once

#include <functional>
#include "Entity.h"
#include "Vector.h"

namespace XYZRoguelike
{
	// Exit of a location. Closed it is a solid wall tile; open it becomes a trigger the player walks into.
	class Door : public Entity
	{
	public:
		Door(const XYZEngine::Vector2Df& position);

		void SetOpen(bool open);
		bool IsOpen() const { return isOpen; }

		// Called once the player steps into the open door
		void SetOnPlayerEnter(std::function<void()> callback);

	private:
		bool isOpen = false;
		bool entered = false;
		std::function<void()> onPlayerEnter;
	};
}
