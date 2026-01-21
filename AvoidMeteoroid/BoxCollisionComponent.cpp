#include"BoxCollisionComponent.h"
#include"CircleCollisionComponent.h"

BoxCollisionComponent::BoxCollisionComponent(Actor* owner) : CollisionComponent(owner), mWidth(0), mHeight(0) {
}

BoxCollisionComponent::~BoxCollisionComponent() {
}

bool BoxCollisionComponent::Intersects(const CollisionComponent& other)const{
	return other.IntersectsBox(*this);
}

bool BoxCollisionComponent::IntersectsCircle(const CircleCollisionComponent& other)const {
	return false;
}

bool BoxCollisionComponent::IntersectsBox(const class BoxCollisionComponent& other)const {
	Vector2 aPos = mOwner->GetPosition();
	Vector2 bPos = other.mOwner->GetPosition();

	float aLeft = aPos.x - mOwner->GetScale() * mWidth / 2;
	float aRight = aPos.x + mOwner->GetScale() * mWidth / 2;
	float aUp = aPos.y - mOwner->GetScale() * mHeight / 2;
	float aDown = aPos.y + mOwner->GetScale() * mHeight / 2;

	float bLeft = bPos.x - other.GetOwner()->GetScale() * other.mWidth / 2;
	float bRight = bPos.x + other.GetOwner()->GetScale() * other.mWidth / 2;
	float bUp = bPos.y - other.GetOwner()->GetScale() * other.mHeight / 2;
	float bDown = bPos.y + other.GetOwner()->GetScale() * other.mHeight / 2;

	if (aRight < bLeft) return false;
	if (aLeft > bRight) return false;
	if (aUp > bDown) return false;
	if (aDown < bUp) return false;

	return true;
}