#pragma once

#include <functional>
#include <string>
#include "Component.h"

namespace XYZEngine
{
	// Health points and armour of a game object. Armour is subtracted from every hit,
	// but a hit always deals at least one point so a fight can never stall.
	class HealthComponent : public Component
	{
	public:
		HealthComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetMaxHealth(float newMaxHealth);
		void SetArmor(float newArmor);

		float GetHealth() const { return health; }
		float GetMaxHealth() const { return maxHealth; }
		float GetArmor() const { return armor; }
		bool IsDead() const { return isDead; }

		// Returns the damage actually taken after armour
		float TakeDamage(float amount, const std::string& source);
		void Heal(float amount);

		void SetOnDeath(std::function<void()> callback);

	private:
		float maxHealth = 100.f;
		float health = 100.f;
		float armor = 0.f;
		bool isDead = false;
		bool lowHealthReported = false;
		std::function<void()> onDeath;
	};
}
