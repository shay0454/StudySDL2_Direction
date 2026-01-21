#include"AsteroidGame.h"
#include"Ship.h"
#include"Asteroid.h"
#include<algorithm>

AsteroidGame::AsteroidGame(){}

void AsteroidGame::OnActorCreated(Actor* actor) {
	if (auto ast = dynamic_cast<Asteroid*>(actor)) {
		mAsteroids.emplace_back(ast);
	}
	else if (auto ship = dynamic_cast<Ship*>(actor)) {
		mShip = ship;
	}
}

void AsteroidGame::OnActorDestroyed(Actor* actor) {
	if (auto ast = dynamic_cast<Asteroid*>(actor)) {
		auto iter = find(mAsteroids.begin(), mAsteroids.end(), ast);
		iter_swap(iter, mAsteroids.end() - 1);
		mAsteroids.pop_back();
	}
	else if (auto ship = dynamic_cast<Ship*>(actor)) {
	}
}

void AsteroidGame::AddAsteroid(Asteroid* ast) {
	mAsteroids.emplace_back(ast);
}

void AsteroidGame::RemoveAstroid(Asteroid* ast) {
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end()) {
		mAsteroids.erase(iter);
	}
}

//사용 데이터 로드
void AsteroidGame::LoadData() {

	SpawnActor<Ship>();
	mShip->SetPosition(Vector2(512.f, 384.f));
	mShip->SetRotation(Math::PiOver2);

	for (int i = 0; i < 20; i++) {
		SpawnActor<Asteroid>();
	}
}

void AsteroidGame::UpdateGame(){
 	Game::UpdateGame();

	if (mShip->IsDead()) {
		if (mShip->GetRespawnTimer() <= 0.0f) {
			mShip->Respawn();
		}
	}
}