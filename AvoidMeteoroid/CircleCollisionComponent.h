#pragma once
#include"CollisionComponent.h"
#include"Math.h"

class CircleCollisionComponent : public CollisionComponent {
	public:
		CircleCollisionComponent(class Actor* owner);

		bool Intersects(const CollisionComponent& other)const override;
		bool IntersectsCircle(const class CircleCollisionComponent& other)const override;
		bool IntersectsBox(const class BoxCollisionComponent& other)const override;

		void SetRadius(float radius) { mRadius = radius; }
		float GetRadius()const;

		const Vector2& GetCenter() const;

	private:
	float mRadius;
};
