#pragma once
#include"Game.h"

class AsteroidGame : public Game {
public:
	AsteroidGame();
	void OnActorCreated(Actor* actor) override;
	void OnActorDestroyed(Actor* actor) override;
	void AddAsteroid(class Asteroid* ast);
	void RemoveAstroid(class Asteroid* ast);

	void UpdateGame()override;

	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }

private:
	void LoadData() override;

	class Ship* mShip; // 플레이 액터
	std::vector<class Asteroid*> mAsteroids;
};