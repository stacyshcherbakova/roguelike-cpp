#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
	{
		view = new sf::View(sf::FloatRect(0, 0, 800, -600));
		transform = gameObject->GetComponent<TransformComponent>();
	}
	CameraComponent::~CameraComponent()
	{
		delete view;
	}

	void CameraComponent::Update(float deltaTime)
	{
		if (window == nullptr)
		{
			return;
		}

		auto position = transform->GetWorldPosition();
		auto rotation = transform->GetWorldRotation();

		view->setCenter(Convert<sf::Vector2f, Vector2Df>(position));
		view->setRotation(rotation);

		window->setView(*view);
	}
	void CameraComponent::Render()
	{
	}

	void CameraComponent::SetBaseResolution(int width, int height)
	{
		view->reset(sf::FloatRect(0, 0, width, -height));
	}
	void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
	{
		if (newWindow == nullptr)
		{
			LOG_ERROR("Camera of '" << gameObject->GetName() << "' received a null window");
		}
		window = newWindow;
	}
	void CameraComponent::ZoomBy(float newZoom)
	{
		if (newZoom <= 0)
		{
			LOG_WARNING("Zoom must be positive, got " << newZoom);
			return;
		}
		view->zoom(newZoom);
	}
}