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
    // Defining colors
    Color lightGreen = { 144, 238, 144, 255 };
    Color darkRed = { 139, 0, 0, 255 };
    Color darkBlue = { 0, 0, 139, 255 };

    // Window dimensions
    int offset = 80;
    int widthOfWindow = 1080;
    int heightOfWindow = 720;

    // Window initialization
    InitWindow(widthOfWindow + offset, heightOfWindow + offset * 2, "Space Invaders(C++ project)");
    InitAudioDevice();

    Font font = LoadFont("Font/yuyimai.ttf");
    if (font.texture.id == 0) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    Texture2D spaceshipImage = LoadTexture("Graphics/heart.png");
    if (spaceshipImage.id == 0) {
        std::cerr << "Error loading image!" << std::endl;
        return -1;
    }

    SetTargetFPS(60);

    // Creating the Game object
    Game game;
    bool showIntro = true; // Shows intro screen initially
    bool showVictory = false; // Shows victory screen when player wins

    // Game loop
    while (!WindowShouldClose()) {
        // Input handling
        if (showIntro) {
            if (IsKeyPressed(KEY_ENTER)) {
                showIntro = false;
                game.isRunning = true;  // Start the game
            }
        }
        else if (game.IsAllAliensDefeated()) {
            showVictory = true;
            if (IsKeyPressed(KEY_ENTER)) {
                showVictory = false;
                game.Restart();
                game.GameInitialization();
            }
        }
        else {
            UpdateMusicStream(game.music);
            game.HandleInput();
            game.Update();

            if (game.IsAllAliensDefeated()) { // Check if all aliens are dead
                showVictory = true;
            }
        }

        BeginDrawing();
        ClearBackground(lightGreen);

        if (showIntro) {
            // Intro screen
            for (int i = 0; i < 720; i++) {
                Color gradientColor = { 144, 238, 144, 255 - i / 3 };
                DrawRectangle(0, i, 1160, 1, gradientColor);
            }

            DrawTextEx(font, "WELCOME TO SPACE INVADERS!", { 200, 150 }, 50, 2, darkBlue);
            DrawRectangle(200, 240, 760, 5, darkBlue);
            DrawTextEx(font, "CONTROLS", { 200, 270 }, 40, 2, darkBlue);
            DrawTextEx(font, "> Move Left:   Arrow Left", { 220, 330 }, 30, 1, darkRed);
            DrawTextEx(font, "> Move Right:  Arrow Right", { 220, 370 }, 30, 1, darkRed);
            DrawTextEx(font, "> Shoot:       Spacebar", { 220, 410 }, 30, 1, darkRed);
            DrawRectangleRounded({ 200, 500, 760, 60 }, 0.2f, 5, darkBlue);
            DrawTextEx(font, "PRESS ENTER TO START", { 230, 515 }, 30, 2, WHITE);
        }
        else if (showVictory) {
            // Victory screen
            ClearBackground(darkBlue);
            DrawTextEx(font, "CONGRATULATIONS!", { 300, 200 }, 50, 2, WHITE);
            DrawTextEx(font, "YOU WIN!", { 450, 270 }, 40, 2, WHITE);
            std::string totalScoreText = "TOTAL SCORE: " + FormatWithLeadingZeros(game.score, 6);
            DrawTextEx(font, totalScoreText.c_str(), { 400, 350 }, 40, 2, WHITE);
            DrawRectangleRounded({ 300, 500, 560, 60 }, 0.2f, 5, darkRed);
            DrawTextEx(font, "PRESS ENTER TO RESTART", { 330, 515 }, 30, 2, WHITE);
        }
        else {
            // Game screen
            DrawRectangleRoundedLines({ 10, 10, 1140, 800 }, 0.18f, 20, darkRed);

            if (game.isRunning) {
                DrawTextEx(font, "LEVEL 01", { 1000, 850 }, 34, 2, darkRed);
            }
            else {
                DrawTextEx(font, "GAME OVER", { 950, 850 }, 34, 2, darkRed);
            }

            float x = 50.0;
            for (int i = 0; i < game.lives; i++) {
                DrawTextureV(spaceshipImage, { x - 50, 815 }, WHITE);
                x += 50;
            }

            DrawTextEx(font, "SCORE:", { 500, 850 }, 34, 2, darkRed);
            std::string scoreText = FormatWithLeadingZeros(game.score, 6);
            DrawTextEx(font, scoreText.c_str(), { 630, 850 }, 34, 2, darkRed);
            game.Draw();
        }

        EndDrawing();
    }

    // Closing the window and audio device
    CloseWindow();
    CloseAudioDevice();
}
