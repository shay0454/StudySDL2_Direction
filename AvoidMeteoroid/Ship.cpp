#include"Ship.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"InputComponent.h"
#include"TextComponent.h"
#include"CircleComponent.h"
#include"AsteroidGame.h"
#include"Math.h"
#include"Laser.h"
#include"Asteroid.h"
#include"AsteroidGame.h"
Ship::Ship(Game* game):Actor(game) {
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_D);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_A);
	ic->SetMaxForwardSpeed(300.f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(32.0f);

}

void Ship::UpdateActor(float deltaTime) {
	mLaserCooldown -= deltaTime;

	auto myGame = dynamic_cast<AsteroidGame*>(GetGame());
	for (auto ast :myGame->GetAsteroids()) {
		if (Intersect(*mCircle, *(ast->GetCircle()))){
			SetState(EDead);
			break;
		}
	}
}

void Ship::ActorInput(const uint8_t* keyState) {
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		Laser* laser = GetGame()->SpawnActor<Laser>();
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
	}
	//mLaserCooldown = 0.5f;
}