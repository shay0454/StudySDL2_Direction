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
	void Update(float deltaTime);// ������Ʈ
	void UpdateComponents(float deltaTime);//������Ʈ ������Ʈ
	virtual void UpdateActor(float deltaTime);//���� ������Ʈ

	void AddComponent(class Component* component);//������Ʈ �߰�
	void RemoveComponent(class Component* component);//������Ʈ ����

	void virtual OnCollision(Actor* other) {};//�浹��

	void ProcessInput(const uint8_t* keyState);
	void virtual ActorInput(const uint8_t* keyState) {}


	void SetPosition(Vector2 position) { mPosition = position; }
	Vector2 GetPosition() const { return mPosition; }

	void SetState(State state) { mState = state; }
	State GetState() const { return mState; }

	void SetScale(float scale) { mScale = scale; }
	float GetScale() const { return mScale; }

	void SetRotation(float rotation) { mRotation = rotation; }
	float GetRotation() const { return mRotation; }

	Vector2 GetForward()const;

	class Game* GetGame() const { return mGame; }



private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	vector<class Component*> mComponents;
	class Game* mGame;
};

#endif // !ACTOR_H