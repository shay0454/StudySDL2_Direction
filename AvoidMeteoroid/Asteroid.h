#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H
#include"Actor.h"
#include<unordered_map>
class Asteroid : public Actor {
	public:
		Asteroid(class Game* game);
		~Asteroid();

};

#endif // !ASTEROID_H
