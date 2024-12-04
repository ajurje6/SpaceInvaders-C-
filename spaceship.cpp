#include "spaceship.hpp"
#include <iostream>
Spaceship::Spaceship()
{
    image = LoadTexture("./Graphics/spaceship.png");
    // Checks if the texture loaded successfully
    if (image.id == 0) {
        std::cerr << "Error loading spaceship texture!" << std::endl;
    }
    // Initialize the spaceship's position to be centered horizontally and at the bottom of the screen vertically
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 75;
    FireTime = 0.0;
    laserSound = LoadSound("/Music/laser.ogg");
}

Spaceship::~Spaceship() {
    // Unload the texture when the spaceship is destroyed
    UnloadTexture(image);
    UnloadSound(laserSound);
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE); //draws the spaceship
}
void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height -75;
    lasers.clear();
}
void Spaceship::MoveRight() {
    position.x += 5;
    //spaceship cant move beyond the right edge screen
    if (position.x > GetScreenWidth() - image.width -25) {
        position.x = GetScreenWidth() - image.width -25;
    }
}
void Spaceship::MoveLeft() {
    position.x -= 5;
    //spaceship cant move beyond the left edge screen
    if (position.x < 25) {
        position.x = 25;
    }
}
void Spaceship::FireLaser() {
    // Checks if enough time has passed since the last shot
    if (GetTime() - FireTime >= 0.35) {
        // The laser's position is at the center of the spaceship and little bit above its current position
        lasers.push_back(Laser({ position.x + image.width / 2 - 2,position.y }, -5));
        // Updates the last fire time to the current time
        FireTime = GetTime();
        PlaySound(laserSound);
    }
}

Rectangle Spaceship::getRect()
{
    // Creates and returns a Rectangle that represents spaceships position and dimension
    return {position.x, position.y, float(image.width), float(image.height)};
}
