#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 100;
}

Spaceship::~Spaceship() {
    UnloadTexture(image);
 
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}
void Spaceship::MoveRight() {
    position.x += 5;
    if (position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}
void Spaceship::MoveLeft() {
    position.x -= 5;
    if (position.x < 0) {
        position.x = 0;
    }
}