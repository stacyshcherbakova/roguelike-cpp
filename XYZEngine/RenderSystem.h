#pragma once

#include <SFML/Graphics.hpp>

namespace XYZEngine
{
	class RenderSystem
	{
	public:
		static RenderSystem* Instance();

		void SetMainWindow(sf::RenderWindow* newWindow);
		// Throws std::runtime_error if no window was set
		sf::RenderWindow& GetMainWindow() const;

		void Render(const sf::Drawable& drawable);

	private:
		sf::RenderWindow* window = nullptr;

		RenderSystem() {}
		~RenderSystem() {}

		RenderSystem(RenderSystem const&) = delete;
		RenderSystem& operator= (RenderSystem const&) = delete;
	};
}