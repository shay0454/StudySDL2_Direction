#include"Laser.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"Game.h"
#include"CircleComponent.h"
#include"Asteroid.h"
#include"TextComponent.h"
#include"AsteroidGame.h"

Laser::Laser(Game* game):Actor(game),mDeathTimer(1.0f) {
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);

}

void Laser::UpdateActor(float deltaTime) {

	mDeathTimer -= deltaTime;

	if (mDeathTimer <= deltaTime) {
		SetState(EDead);
	}
	else {
		auto myGame = dynamic_cast<AsteroidGame*>(GetGame());
 		for (auto ast : myGame->GetAsteroids()) {
			if (Intersect(*mCircle, *(ast->GetCircle()))) {
				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
}