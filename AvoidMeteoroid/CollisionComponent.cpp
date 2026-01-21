#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Actor *owner) : Component(owner){
	owner->GetGame()->AddCollider(this);
}

CollisionComponent::~CollisionComponent(){
	mOwner->GetGame()->RemoveCollider(this);
}