#pragma once
#include <raylib.h>
class Laser {
public:
	Laser(Vector2 position, int speed);
	void DrawLaser();
	void UpdateLaser();
	bool IsActive;
	Rectangle getRect();
private:
	Vector2 position;
	int speed;
};