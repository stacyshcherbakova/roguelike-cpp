#include "pch.h"
#include "SpriteMovementAnimationComponent.h"
#include "GameObject.h"
#include "Logger.h"
#include "ResourceSystem.h"

namespace XYZEngine
{
	SpriteMovementAnimationComponent::SpriteMovementAnimationComponent(GameObject* gameObject) : Component(gameObject)
	{
		movement = gameObject->GetComponent<MovementComponent>();
		renderer = gameObject->GetComponent<SpriteRendererComponent>();

		if (movement == nullptr || renderer == nullptr)
		{
			LOG_WARNING("'" << gameObject->GetName() << "' needs MovementComponent and SpriteRendererComponent for the movement animation");
		}
	}

	void SpriteMovementAnimationComponent::Initialize(const std::string& textureMapName, float framesPerSecond)
	{
		frames.clear();
		const int count = ResourceSystem::Instance()->GetTextureMapElementsCount(textureMapName);
		if (count == 0)
		{
			LOG_ERROR("Animation of '" << gameObject->GetName() << "' has no frames: texture map '" << textureMapName << "' is empty");
		}
		for (int i = 0; i < count; i++)
		{
			frames.push_back(ResourceSystem::Instance()->GetTextureMapElementShared(textureMapName, i));
		}

		secondsPerFrame = framesPerSecond > 0.f ? 1.f / framesPerSecond : 0.1f;
		frame = 0;
		counter = 0.f;

		if (!frames.empty() && renderer != nullptr)
		{
			renderer->SetTexture(*frames[0]);
		}
	}

	void SpriteMovementAnimationComponent::Update(float deltaTime)
	{
		if (movement == nullptr || renderer == nullptr || frames.empty())
		{
			return;
		}

		if (!movement->IsMoving())
		{
			if (frame != 0)
			{
				frame = 0;
				counter = 0.f;
				renderer->SetTexture(*frames[0]);
			}
			return;
		}

		renderer->FlipX(movement->GetFacing().x < 0.f);

		counter += deltaTime;
		if (counter >= secondsPerFrame)
		{
			counter -= secondsPerFrame;
			frame = (frame + 1) % (int)frames.size();
			renderer->SetTexture(*frames[frame]);
		}
	}

	void SpriteMovementAnimationComponent::Render()
	{
	}
}
