#include<iostream>
#include<SDL.h>
#include"Game.h"
#include"AvoidAstroidGame.h"

int main(int argc, char** argv) {
	AvoidAstroidGame game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}