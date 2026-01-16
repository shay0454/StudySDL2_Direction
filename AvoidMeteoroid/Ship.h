#pragma once
#ifndef SHIP_H
#define SHIP_H
#include"Actor.h"
class Ship : public  Actor {
	public:
		Ship(class Game* game);

		void UpdateActor(float deltaTime) override;
		void ActorInput(const uint8_t* keyState) override;

	private:
		float mLaserCooldown;

};
#endif // !SHIP_H
