#include<iostream>
#include<SDL.h>
#include"Game.h"
#include"AsteroidGame.h"
int main(int argc, char** argv) {
	AsteroidGame game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}