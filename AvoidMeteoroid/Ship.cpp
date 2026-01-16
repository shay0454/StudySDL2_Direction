#include"Ship.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"InputComponent.h"
#include"TextComponent.h"
#include"Math.h"
#include"Laser.h"
#include"Asteroid.h"
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


}

void Ship::UpdateActor(float deltaTime) {
	mLaserCooldown -= deltaTime;

}

void Ship::ActorInput(const uint8_t* keyState) {

}