#include <iostream>
#include <raylib.h>
#include "game.hpp"
#include <string>
using namespace std;
std::string FormatWithLeadingZeros(int number, int width) {
	std::string numberText = std::to_string(number);
	int leadingZeros = width - numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}
int main() {
	// Defining a light green color
	Color lightGreen = { 144, 238, 144, 255 }; // RGB for light green
	Color darkRed = { 139, 0, 0, 255 };//RGB for red
	//Window dimensions
	int offset = 80;
	int widthOfWindow = 1080;
	int heightOfWindow = 720;
	//Window inicialization
	InitWindow(widthOfWindow + offset, heightOfWindow + offset * 2, "Space Invaders(C++ project)");
	InitAudioDevice();
	Font font = LoadFont("Font/yuyimai.ttf");
	if (font.texture.id == 0) {
		std::cerr << "Error loading font!" << std::endl;
		return -1; // Exit the program with an error code
	}
	Texture2D spaceshipImage = LoadTexture("Graphics/heart.png");
	if (spaceshipImage.id == 0) {
		std::cerr << "Error loading image!" << std::endl;
		return -1; // Exit the program with an error code
	}
	SetTargetFPS(60);
	//Creating the Game object
	Game game;
	//GameLoop
	while (WindowShouldClose() == false) {
		UpdateMusicStream(game.music);
		game.HandleInput();
		game.Update();
		BeginDrawing();
		ClearBackground(lightGreen);
		DrawRectangleRoundedLines({ 10, 10, 1140, 800 }, 0.18f, 20, darkRed);
	    if (game.isRunning) {
			DrawTextEx(font, "LEVEL 01", { 1000, 850 }, 34, 2, darkRed);
		}
		else {
			DrawTextEx(font, "GAME OVER", { 950, 850 }, 34, 2, darkRed);
		}
		float x = 50.0;
		for (int i = 0; i < game.lives; i++) {
			DrawTextureV(spaceshipImage, { x-50, 815 }, WHITE);
			x += 50;
		}
	DrawTextEx(font, "SCORE:", { 500, 850 }, 34, 2, darkRed);
	std::string scoreText = FormatWithLeadingZeros(game.score, 6);
	DrawTextEx(font, scoreText.c_str(), { 630, 850 }, 34, 2, darkRed);
	game.Draw();
	EndDrawing();

	}
	//Closing the window and audio device
	CloseWindow();
	CloseAudioDevice();
}