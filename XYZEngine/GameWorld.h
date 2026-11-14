#pragma once

#include <functional>
#include <string>
#include <vector>
#include "GameObject.h"
#include "PhysicsSystem.h"

namespace XYZEngine
{
	class GameWorld
	{
	public:
		static GameWorld* Instance();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void LateUpdate();

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(std::string name);
		void DestroyGameObject(GameObject* gameObject);
		void Clear();

		std::vector<GameObject*> FindGameObjectsByName(const std::string& name) const;

		// Runs the action at the end of the frame, after destroyed objects are gone.
		// Safe way to rebuild the world from inside a component callback.
		void RunLater(std::function<void()> action);

		void Print() const;
	private:
		GameWorld() {}
		~GameWorld() {}

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		float fixedCounter = 0.f;

		std::vector<GameObject*> gameObjects = {};
		std::vector<GameObject*> markedToDestroyGameObjects = {};
		std::vector<std::function<void()>> deferredActions;

		void DestroyGameObjectImmediate(GameObject* gameObject);
	};
}
