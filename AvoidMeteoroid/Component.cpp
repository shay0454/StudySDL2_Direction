#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder) :mOwner(owner), mUpdateOrder(updateOrder){
	mOwner->AddComponent(this);
}

Component::~Component() {
	mOwner->RemoveComponent(this);
}

//업데이트
void Component::Update(float deltaTime){}

//Draw
void Component::Draw(SDL_Renderer* renderer) {}