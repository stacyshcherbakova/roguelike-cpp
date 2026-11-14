#pragma once

#include "ColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include <SFML/Graphics/Sprite.hpp>

namespace XYZEngine
{
	class SpriteColliderComponent : public ColliderComponent
	{
	public:
		SpriteColliderComponent(GameObject* gameObject);
		~SpriteColliderComponent();

		void Update(float deltaTime) override;
		void Render() override;

		// Debug outline around every sprite collider
		static void SetDrawBounds(bool draw);

	private:
		const sf::Sprite* sprite = nullptr;
		static bool drawBounds;
	};
}

