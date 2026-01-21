#include"Laser.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"Game.h"
#include"CircleCollisionComponent.h"
#include"BoxCollisionComponent.h"
#include"Asteroid.h"
#include"TextComponent.h"
#include"AsteroidGame.h"

Laser::Laser(Game* game):Actor(game),mDeathTimer(1.0f) {
	mSprite = new SpriteComponent(this);
	mSprite->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.f);

	CircleCollisionComponent* mCircle = new CircleCollisionComponent(this);
	mCircle->SetRadius(11.0f);
	SetCollision(mCircle);
}

void Laser::UpdateActor(float deltaTime) {

	mDeathTimer -= deltaTime;

	if (mDeathTimer <= deltaTime) {
		SetState(EDead);
	}
}

void Laser::OnCollision(Actor* other) {
	if (GetState() == EDead)return;
	if (dynamic_cast<Asteroid*>(other)) {
		SetState(EDead);
	}
}