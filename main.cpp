#include <iostream>
#include <raylib.h>
#include "game.hpp"
using namespace std;
int main() {
	// Define a light green color
	Color lightGreen = { 144, 238, 144, 255 }; // RGB for light green
	//Window dimensions
	int widthOfWindow = 1080;
	int heightOfWindow = 720;
	//Window inicialization
	InitWindow(widthOfWindow, heightOfWindow, "Space Invaders(C++ project)");
	SetTargetFPS(60);
	//Creating the Game object
	Game game;
	//GameLoop
	while (WindowShouldClose() == false) {
		game.HandleInput();
		BeginDrawing();
		ClearBackground(lightGreen);
		game.Draw();
		EndDrawing();

	}
	//Closing the window
	CloseWindow();
}