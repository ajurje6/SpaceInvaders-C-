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
		if (position.y > GetScreenHeight() || position.y < 0) {
			IsActive = false;
		}
	}
}