#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include "Component.h"
#include "MovementComponent.h"
#include "SpriteRendererComponent.h"

namespace XYZEngine
{
	// Cycles the frames of a texture map while the object moves and faces the sprite along the movement
	class SpriteMovementAnimationComponent : public Component
	{
	public:
		SpriteMovementAnimationComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void Initialize(const std::string& textureMapName, float framesPerSecond);

	private:
		MovementComponent* movement = nullptr;
		SpriteRendererComponent* renderer = nullptr;

		std::vector<const sf::Texture*> frames;
		float secondsPerFrame = 0.1f;
		float counter = 0.f;
		int frame = 0;
	};
}
