#include"Ship.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"InputComponent.h"
#include"TextComponent.h"
#include"CircleCollisionComponent.h"
#include"BoxCollisionComponent.h"
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

	CircleCollisionComponent *mCircle = new CircleCollisionComponent(this);
	mCircle->SetRadius(32.0f);
	SetCollision(mCircle);

	mText = new TextComponent(this);
}

void Ship::UpdateActor(float deltaTime) {
	mText->SetText(to_string( mInput->GetForwardSpeed()));
	mLaserCooldown -= deltaTime;
	if (IsDead()) { 
		mRespawnTimer -= deltaTime;
		return; }
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
	GetGame()->RemoveCollider(GetCollision());
	mInput->SetActive(false);
	SetRespawnTimer(3.0f);
}

void Ship::Respawn() {
	mDead = false;
	GetGame()->AddCollider(GetCollision());
	mInput->SetActive(true);
	SetRespawnTimer(0.0f);
}

void Ship::OnCollision(Actor* other) {
	if (GetState() == EDead)return;
	if (dynamic_cast<Asteroid*>(other)) {
		Die();
	}
}