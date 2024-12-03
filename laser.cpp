#include "laser.hpp"
#include <iostream>
using namespace std;
Laser::Laser(Vector2 position,int speed) {
	this->position = position;
	this->speed = speed;
	IsActive = true;
}
void Laser::DrawLaser() {
	if (IsActive) {
		DrawRectangle(position.x, position.y, 5, 15, RED);
	}
}
void Laser::UpdateLaser() {
	position.y += speed;
	if (IsActive) {
		if (position.y > GetScreenHeight() -75 || position.y < 10) {
			IsActive = false;
		}
	}
}

Rectangle Laser::getRect()
{
    Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 5;
	rect.height = 15;
	return rect;
}
