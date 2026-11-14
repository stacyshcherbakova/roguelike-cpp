#pragma once

namespace XYZEngine
{
	class ColliderComponent;
	struct Trigger
	{
	public:
		Trigger(ColliderComponent* newFirst, ColliderComponent* newSecond) :
			first(newFirst), second(newSecond) {
		};

		ColliderComponent* GetFirst() const { return first; }
		ColliderComponent* GetSecond() const { return second; }
		// The collider on the other side of the trigger pair
		ColliderComponent* GetOther(const ColliderComponent* self) const { return self == first ? second : first; }
	private:
		ColliderComponent* first;
		ColliderComponent* second;
	};
}
