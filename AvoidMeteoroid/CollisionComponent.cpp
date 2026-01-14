#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Actor *owner) : Component(owner),mWidth(0),mHeight(0){
	owner->GetGame()->AddCollider(this);
}

CollisionComponent::~CollisionComponent(){
	mOwner->GetGame()->RemoveCollider(this);
}

bool CollisionComponent::Intersect(const CollisionComponent* other) const{
	Vector2 aPos = mOwner->GetPosition();
	Vector2 bPos = other->mOwner->GetPosition();

	float aLeft = aPos.x - mOwner->GetScale()*mWidth / 2;
	float aRight = aPos.x + mOwner->GetScale() * mWidth / 2;
	float aUp = aPos.y - mOwner->GetScale() * mHeight / 2;
	float aDown = aPos.y + mOwner->GetScale() * mHeight / 2;

	float bLeft = bPos.x - other->GetOwner()->GetScale() * other->mWidth / 2;
	float bRight = bPos.x + other->GetOwner()->GetScale() * other->mWidth / 2;
	float bUp = bPos.y - other->GetOwner()->GetScale() * other->mHeight / 2;
	float bDown = bPos.y + other->GetOwner()->GetScale() * other->mHeight / 2;

	if (aRight < bLeft) return false;
	if (aLeft > bRight) return false;
	if (aUp > bDown) return false;
	if (aDown < bUp) return false;

	return true;
}