#pragma once
#include"CollisionComponent.h"

class BoxCollisionComponent : public CollisionComponent {
	public:
		BoxCollisionComponent(class Actor* owner);
		~BoxCollisionComponent();

		void SetSize(float w, float h) { mWidth = w, mHeight = h; }

		bool Intersects(const CollisionComponent& other) const override;

		bool IntersectsBox(const class BoxCollisionComponent& other)const override;
		bool IntersectsCircle(const class CircleCollisionComponent& other)const override;

private:
	float mWidth;
	float mHeight;

	class Vector2 min;
	class Vector2 max;
};