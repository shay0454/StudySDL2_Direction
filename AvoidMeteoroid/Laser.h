#pragma once
#include"Actor.h"
class Laser : public Actor {
public:
	Laser(class Game* game);

	void UpdateActor(float deltaTime) override;
	void OnCollision(Actor* other)override;
private:
	float mDeathTimer;
	class SpriteComponent* mSprite;
};