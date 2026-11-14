#pragma once

#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include "Component.h"

namespace XYZEngine
{
	// Calls a function once each time a key goes down
	class KeyActionComponent : public Component
	{
	public:
		KeyActionComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void Bind(sf::Keyboard::Key key, std::function<void()> action);

	private:
		sf::Keyboard::Key key = sf::Keyboard::Unknown;
		bool held = false;
		std::function<void()> action;
	};
}
