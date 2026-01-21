#include"CircleCollisionComponent.h"
#include"BoxCollisionComponent.h"
CircleCollisionComponent::CircleCollisionComponent(Actor* owner) :CollisionComponent(owner),mRadius(0.0f) {
}

const Vector2& CircleCollisionComponent::GetCenter()const {
	return mOwner->GetPosition();
}

float CircleCollisionComponent::GetRadius()const {
	return mOwner->GetScale() * mRadius;
}

bool CircleCollisionComponent::Intersects(const CollisionComponent& other) const {
	return other.IntersectsCircle(*this);
}

bool CircleCollisionComponent::IntersectsCircle(const CircleCollisionComponent& other)const{
	Vector2 diff = this->GetCenter() - other.GetCenter();
	float distSq = diff.LengthSq();

	float radiiSq = this->GetRadius() + other.GetRadius();
	radiiSq *= radiiSq;
	return distSq <= radiiSq;
}

bool CircleCollisionComponent::IntersectsBox(const BoxCollisionComponent& other)const {
	return false;
}