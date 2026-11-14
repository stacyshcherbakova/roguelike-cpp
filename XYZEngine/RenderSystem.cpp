#include "pch.h"
#include "RenderSystem.h"
#include "Logger.h"

#include <stdexcept>

namespace XYZEngine
{
	RenderSystem* RenderSystem::Instance()
	{
		static RenderSystem render;
		return &render;
	}

	void RenderSystem::SetMainWindow(sf::RenderWindow* newWindow)
	{
		window = newWindow;
		if (window != nullptr)
		{
			LOG_INFO("Main window set: " << window->getSize().x << "x" << window->getSize().y);
		}
	}
	sf::RenderWindow& RenderSystem::GetMainWindow() const
	{
		if (window == nullptr)
		{
			throw std::runtime_error("The main window is requested before it was set");
		}
		return *window;
	}

	void RenderSystem::Render(const sf::Drawable& drawable)
	{
		if (window != nullptr)
		{
			window->draw(drawable);
		}
	}
}