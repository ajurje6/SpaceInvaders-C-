#include "mysteryship.hpp"
MysteryShip::MysteryShip() {
	image = LoadTexture("Graphics/mystery.png");
	alive = false;
}
MysteryShip::~MysteryShip() {
	UnloadTexture(image);
}

void MysteryShip::UpdateMysteryShip()
{
	if (alive) {
	position.x += speed;
	if (position.x > GetScreenWidth() - image.width -10 || position.x < 10) {
	alive = false;
	}
    }
}

void MysteryShip::DrawMysteryShip()
{
	if (alive) {
		DrawTextureV(image, position, RED);
	}
}

void MysteryShip::SpawnMysteryShip()
{
	position.y = 30;
	int spawnSide = GetRandomValue(0, 1);
	if (spawnSide == 0 ) {
		position.x = 10;
		speed = 3;
	}
	else{
		position.x = GetScreenWidth() - image.width -10;
		speed = -3;
	}
	alive = true;
}

Rectangle MysteryShip::getRect()
{
	if (alive) {
		return { position.x,position.y,float(image.width),float(image.height)};
	}
	else {
		return { position.x,position.y,0,0 };
	}
}
