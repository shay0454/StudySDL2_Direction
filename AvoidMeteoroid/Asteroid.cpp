#include"Asteroid.h"
#include "Game.h"
#include "Random.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"CircleCollisionComponent.h"
#include"BoxCollisionComponent.h"
#include"Math.h"
Asteroid::Asteroid(Game* game):Actor(game){
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	
	SpriteComponent* sc = new SpriteComponent(this); 
	sc->SetTexture(  game->GetTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);

	CircleCollisionComponent* mCircle = new CircleCollisionComponent(this);
	mCircle->SetRadius(30.0f);
	SetCollision(mCircle);
}

Asteroid::~Asteroid() {
}

void Asteroid::UpdateActor(float deltaTime) {
	Vector2 pos = GetPosition();
	float rot = GetRotation();

	if (pos.x<0.0f || pos.x>screen_width) {
		rot = Math::Pi - GetRotation();
	}
	if (pos.y<0.0f || pos.y>screen_height) {
		rot = -GetRotation();
	}
	SetRotation(rot);

	pos.x = SDL_clamp(pos.x, 0.0f, screen_width);
	pos.y = SDL_clamp(pos.y, 0.0f, screen_height);
	SetPosition(pos);
}

void Asteroid::OnCollision(Actor* other) {
	if (GetState() == EDead)return;
	if (!dynamic_cast<Asteroid*>(other)) {
		SetState(EDead);
	}
}