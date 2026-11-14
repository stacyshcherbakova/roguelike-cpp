#include "pch.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "Logger.h"

#include <algorithm>
#include <cassert>

namespace XYZEngine
{
	HealthComponent::HealthComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void HealthComponent::Update(float deltaTime)
	{
	}

	void HealthComponent::Render()
	{
	}

	void HealthComponent::SetMaxHealth(float newMaxHealth)
	{
		assert(newMaxHealth > 0.f && "Max health must be positive");
		if (newMaxHealth <= 0.f)
		{
			LOG_ERROR("'" << gameObject->GetName() << "' got max health " << newMaxHealth << ", keeping " << maxHealth);
			return;
		}
		maxHealth = newMaxHealth;
		health = newMaxHealth;
		isDead = false;
		lowHealthReported = false;
	}

	void HealthComponent::SetArmor(float newArmor)
	{
		if (newArmor < 0.f)
		{
			LOG_WARNING("'" << gameObject->GetName() << "' got negative armour " << newArmor << ", using 0");
			newArmor = 0.f;
		}
		armor = newArmor;
	}

	float HealthComponent::TakeDamage(float amount, const std::string& source)
	{
		if (isDead)
		{
			return 0.f;
		}
		if (amount <= 0.f)
		{
			LOG_WARNING("'" << gameObject->GetName() << "' received a non-positive hit of " << amount << " from " << source);
			return 0.f;
		}

		const float dealt = std::max(1.f, amount - armor);
		health = std::max(0.f, health - dealt);
		LOG_INFO("'" << gameObject->GetName() << "' takes " << dealt << " damage from " << source
			<< " (" << amount << " minus " << armor << " armour), health " << health << "/" << maxHealth);

		if (!lowHealthReported && health > 0.f && health <= 0.25f * maxHealth)
		{
			lowHealthReported = true;
			LOG_WARNING("'" << gameObject->GetName() << "' is almost dead: " << health << "/" << maxHealth);
		}

		if (health <= 0.f)
		{
			isDead = true;
			LOG_INFO("'" << gameObject->GetName() << "' died");
			if (onDeath)
			{
				onDeath();
			}
		}
		return dealt;
	}

	void HealthComponent::Heal(float amount)
	{
		if (isDead || amount <= 0.f)
		{
			return;
		}
		health = std::min(maxHealth, health + amount);
		if (health > 0.25f * maxHealth)
		{
			lowHealthReported = false;
		}
		LOG_INFO("'" << gameObject->GetName() << "' healed by " << amount << ", health " << health << "/" << maxHealth);
	}

	void HealthComponent::SetOnDeath(std::function<void()> callback)
	{
		onDeath = std::move(callback);
	}
}
