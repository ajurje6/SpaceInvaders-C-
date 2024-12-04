#include "alien.hpp"
#include <iostream>
Texture2D Alien::alienImages[3] = {};
Alien::Alien(int typeOfAlien, Vector2 position) {
    this->typeOfAlien = typeOfAlien;
    this->position = position;
    if (alienImages[typeOfAlien - 1].id == 0) {
        switch (typeOfAlien) {
        case 1:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3:
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            break;
        default:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }

        // Check if the texture loaded successfully
        if (alienImages[typeOfAlien - 1].id == 0) {
            std::cerr << "Error loading alien texture for type " << typeOfAlien << std::endl;
        }
    }
}
 void Alien::DrawAlien() {
	DrawTextureV(alienImages[typeOfAlien-1], position, BLACK);
}

 int Alien::GetTypeOfAlien() {
	 return typeOfAlien;
 }

 Rectangle Alien::getRect()
 {
	 // Creates and returns a Rectangle that represents aliens position and dimension
	 return { position.x, position.y,
	   float(alienImages[typeOfAlien - 1].width),
	   float(alienImages[typeOfAlien - 1].height)
	 };
 }

 void Alien::UnloadImages()
 {
	 for (int i = 0; i < 2; i++) {
		 UnloadTexture(alienImages[i]);
	 }
 }

 void Alien::UpdateAlien(int direction) {
	 position.x += direction;
 }