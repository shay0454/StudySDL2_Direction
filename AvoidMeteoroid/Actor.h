#ifndef ACTOR_H
#define ACTOR_H
#include<iostream>
#include <vector>
#include "Game.h";

using namespace std;

class Actor {
public:
	enum State {
		EActive, EPaused, EDead
	};
	Actor(class Game* game);
	virtual ~Actor();
	void Update(float deltaTime);// 업데이트
	void UpdateComponents(float deltaTime);//컴포넌트 업데이트
	virtual void UpdateActor(float deltaTime);//액터 업데이트

	void AddComponent(class Component* component);//컴포넌트 추가
	void RemoveComponent(class Component* component);//컴포넌트 제거

	void virtual OnCollision(Actor* other) {};//충돌시

	void ProcessInput(const uint8_t* keyState);
	void virtual ActorInput(const uint8_t* keyState) {}


	void SetPosition(Vector2 position) { mPosition = position; }
	const Vector2& GetPosition() const { return mPosition; }

	void SetState(State state) { mState = state; }
	State GetState() const { return mState; }

	void SetScale(float scale) { mScale = scale; }
	float GetScale() const { return mScale; }

	void SetRotation(float rotation) { mRotation = rotation; }
	float GetRotation() const { return mRotation; }

	Vector2 GetForward()const;

	class Game* GetGame() const { return mGame; }

	void SetCollision(class CollisionComponent* collision) { mCollision = collision; }
	class CollisionComponent* GetCollision() const  { return mCollision; }

private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	vector<class Component*> mComponents;
	class Game* mGame;
	class CollisionComponent* mCollision;
};

#endif // !ACTOR_H