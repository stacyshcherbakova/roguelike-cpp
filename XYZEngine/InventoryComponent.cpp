#include "pch.h"
#include "InventoryComponent.h"
#include "GameObject.h"
#include "Logger.h"

namespace XYZEngine
{
	InventoryComponent::InventoryComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void InventoryComponent::Update(float deltaTime)
	{
	}

	void InventoryComponent::Render()
	{
	}

	void InventoryComponent::Add(const std::string& item, int count)
	{
		if (count <= 0)
		{
			LOG_WARNING("Tried to add " << count << " of '" << item << "' to the inventory of '" << gameObject->GetName() << "'");
			return;
		}
		items[item] += count;
		LOG_INFO("'" << gameObject->GetName() << "' picked up " << count << " x '" << item << "', now has " << items[item]);
	}

	bool InventoryComponent::Use(const std::string& item)
	{
		auto found = items.find(item);
		if (found == items.end() || found->second <= 0)
		{
			LOG_DEBUG("'" << gameObject->GetName() << "' has no '" << item << "' to use");
			return false;
		}
		found->second--;
		LOG_INFO("'" << gameObject->GetName() << "' used '" << item << "', " << found->second << " left");
		return true;
	}

	int InventoryComponent::Count(const std::string& item) const
	{
		auto found = items.find(item);
		return found == items.end() ? 0 : found->second;
	}

	void InventoryComponent::Clear()
	{
		items.clear();
	}
}
