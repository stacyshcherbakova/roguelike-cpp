#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Component.h"

namespace XYZEngine
{
	// Text drawn in window coordinates on top of the world, independent of any camera
	class ScreenTextComponent : public Component
	{
	public:
		ScreenTextComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetFont(const sf::Font* font);
		void SetString(const std::string& text);
		void SetCharacterSize(unsigned int size);
		void SetColor(const sf::Color& color);
		// Pixels from the top-left corner of the window
		void SetScreenPosition(float x, float y);
		// Alignment inside the window: 0 = left/top, 0.5 = centre, 1 = right/bottom
		void SetAnchor(float x, float y);

	private:
		sf::Text text;
		sf::Vector2f position = { 0.f, 0.f };
		sf::Vector2f anchor = { 0.f, 0.f };
	};
}
