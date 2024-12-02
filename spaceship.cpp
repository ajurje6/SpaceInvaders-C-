#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("./Graphics/spaceship.png");
    // Initialize the spaceship's position to be centered horizontally and at the bottom of the screen vertically
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height;
    FireTime = 0.0;
}

Spaceship::~Spaceship() {
    // Unload the texture when the spaceship is destroyed
    UnloadTexture(image);
 
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE); //draws the spaceship
}
void Spaceship::MoveRight() {
    position.x += 5;
    //spaceship cant move beyond the right edge screen
    if (position.x > GetScreenWidth() - image.width) {
        position.x = GetScreenWidth() - image.width;
    }
}
void Spaceship::MoveLeft() {
    position.x -= 5;
    //spaceship cant move beyond the left edge screen
    if (position.x < 0) {
        position.x = 0;
    }
}
void Spaceship::FireLaser() {
    // Checks if enough time has passed since the last shot
    if (GetTime() - FireTime >= 0.35) {
        // The laser's position is at the center of the spaceship and little bit above its current position
        lasers.push_back(Laser({ position.x + image.width / 2 - 2,position.y }, -5));
        // Updates the last fire time to the current time
        FireTime = GetTime();
    }
}