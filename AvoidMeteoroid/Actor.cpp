#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "Math.h"

Actor::Actor(Game* game) :mState(EActive), mPosition(Vector2(0, 0)), mScale(1.0f), mRotation(0.0f), mGame(game) {
	mGame->AddActor(this);
}

Actor::~Actor() {
	mGame->RemoveActor(this);
}

//업데이트
void Actor::Update(float deltaTime) {
	if (mState == EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

//컴포넌트 업데이트
void Actor::UpdateComponents(float deltaTime) {
	for (auto comp : mComponents) {
		comp->Update(deltaTime);
	}
}

//액터 업데이트
void Actor::UpdateActor(float deltaTime) {
}

//컴포넌트 추가
void Actor::AddComponent(Component* component) {
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {
		if (myOrder < (*iter)->GetUpdateOrder()) {
			break;
		}
	}
	mComponents.insert(iter, component);
}

//컴포넌트 제거
void Actor::RemoveComponent(Component* component) {
	auto iter = find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}

Vector2 Actor::GetForward() const {
	return Vector2(Math::Cos(mRotation), Math::Sin(mRotation));
}