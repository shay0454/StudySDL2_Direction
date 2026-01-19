#pragma once
#ifndef SHIP_H
#define SHIP_H
#include"Actor.h"
class Ship : public  Actor {
	public:
		Ship(class Game* game);

		void UpdateActor(float deltaTime) override;
		void ActorInput(const uint8_t* keyState) override;

		bool IsDead() { return mDead; }

		void Die();
		void Respawn();

		void SetRespawnTimer(float timer) { mRespawnTimer = timer; }
		const float GetRespawnTimer()const { return mRespawnTimer; }

	private:
		bool mDead = false;
		float mRespawnTimer;
		float mLaserCooldown;
		class CircleComponent* mCircle;
		class InputComponent* mInput;
		class TextComponent* mText;
};
#endif // !SHIP_H
