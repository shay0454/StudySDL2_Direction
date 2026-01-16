#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H
#include"Actor.h"
#include<unordered_map>
class Asteroid : public Actor {
	public:
		Asteroid(class Game* game);
		~Asteroid();

		class CircleComponent* GetCircle() { return mCircle; }

	private:
		class CircleComponent* mCircle;
};

#endif // !ASTEROID_H
