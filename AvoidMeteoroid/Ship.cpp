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

	mInput = new InputComponent(this);
	mInput->SetForwardKey(SDL_SCANCODE_W);
	mInput->SetBackKey(SDL_SCANCODE_S);
	mInput->SetClockwiseKey(SDL_SCANCODE_D);
	mInput->SetCounterClockwiseKey(SDL_SCANCODE_A);
	mInput->SetMaxForwardSpeed(10.f);
	mInput->SetMaxAngularSpeed(Math::Pi/6);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(32.0f);

	mText = new TextComponent(this);
}

void Ship::UpdateActor(float deltaTime) {
	mText->SetText(to_string( mInput->GetForwardSpeed()));
	mLaserCooldown -= deltaTime;
	if (IsDead()) { 
		mRespawnTimer -= deltaTime;
		return; }
	auto myGame = dynamic_cast<AsteroidGame*>(GetGame());
	for (auto ast :myGame->GetAsteroids()) {
		if (Intersect(*mCircle, *(ast->GetCircle()))){
			Die();
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
		mLaserCooldown = 0.5f;
	}
}

void Ship::Die() {
	mDead = true;
	mInput->SetActive(false);
	SetRespawnTimer(3.0f);
}

void Ship::Respawn() {
	mDead = false;
	mInput->SetActive(true);
	SetRespawnTimer(0.0f);
}