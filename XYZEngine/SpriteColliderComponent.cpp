#include "pch.h"
#include "SpriteColliderComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	bool SpriteColliderComponent::drawBounds = false;

	SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject) : ColliderComponent(gameObject)
	{
		auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
		if (spriteRenderer == nullptr)
		{
			LOG_ERROR("'" << gameObject->GetName() << "' needs a SpriteRendererComponent before a SpriteColliderComponent; the collider is disabled");
			return;
		}

		renderer = spriteRenderer;
		sprite = spriteRenderer->GetSprite();
		// Take the bounds right away so a freshly created object never collides at the origin
		renderer->SyncWithTransform();
		bounds = sprite->getGlobalBounds();
		PhysicsSystem::Instance()->Subscribe(this);
	}
	SpriteColliderComponent::~SpriteColliderComponent()
	{
		PhysicsSystem::Instance()->Unsubscribe(this);
	}

	void SpriteColliderComponent::SetDrawBounds(bool draw)
	{
		drawBounds = draw;
	}

	void SpriteColliderComponent::Update(float deltaTime)
	{
		if (sprite != nullptr)
		{
			renderer->SyncWithTransform();
			bounds = sprite->getGlobalBounds();
		}
	}
	void SpriteColliderComponent::Render()
	{
		if (!drawBounds || sprite == nullptr)
		{
			return;
		}

		sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
		rectangle.setPosition(bounds.left, bounds.top);
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color::White);
		rectangle.setOutlineThickness(4);

		RenderSystem::Instance()->Render(rectangle);
	}
}