#include "alien.hpp"
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
	}
}
 void Alien::DrawAlien() {
	DrawTextureV(alienImages[typeOfAlien-1], position, BLACK);
}

 int Alien::GetTypeOfAlien() {
	 return typeOfAlien;
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