#pragma once

#include <map>
#include <string>
#include "Component.h"

namespace XYZEngine
{
	// Counts of items carried by a game object; what an item does is up to the game
	class InventoryComponent : public Component
	{
	public:
		InventoryComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void Add(const std::string& item, int count = 1);
		// Removes one item and returns true, or returns false when there is none
		bool Use(const std::string& item);
		int Count(const std::string& item) const;
		void Clear();

	private:
		std::map<std::string, int> items;
	};
}
