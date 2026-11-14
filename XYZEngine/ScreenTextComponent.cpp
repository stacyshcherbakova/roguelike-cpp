#include "pch.h"
#include "ScreenTextComponent.h"
#include "RenderSystem.h"

namespace XYZEngine
{
	ScreenTextComponent::ScreenTextComponent(GameObject* gameObject) : Component(gameObject)
	{
		text.setCharacterSize(22);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2.f);
	}

	void ScreenTextComponent::Update(float deltaTime)
	{
	}

	void ScreenTextComponent::Render()
	{
		if (text.getFont() == nullptr || text.getString().isEmpty())
		{
			return;
		}

		sf::RenderWindow& window = RenderSystem::Instance()->GetMainWindow();
		const sf::View worldView = window.getView();
		window.setView(window.getDefaultView());

		const sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width * anchor.x, bounds.top + bounds.height * anchor.y);
		const sf::Vector2f windowSize((float)window.getSize().x, (float)window.getSize().y);
		text.setPosition(position.x + windowSize.x * anchor.x, position.y + windowSize.y * anchor.y);

		window.draw(text);
		window.setView(worldView);
	}

	void ScreenTextComponent::SetFont(const sf::Font* font)
	{
		if (font != nullptr)
		{
			text.setFont(*font);
		}
	}

	void ScreenTextComponent::SetString(const std::string& newText)
	{
		text.setString(newText);
	}

	void ScreenTextComponent::SetCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
	}

	void ScreenTextComponent::SetColor(const sf::Color& color)
	{
		text.setFillColor(color);
	}

	void ScreenTextComponent::SetScreenPosition(float x, float y)
	{
		position = { x, y };
	}

	void ScreenTextComponent::SetAnchor(float x, float y)
	{
		anchor = { x, y };
	}
}
