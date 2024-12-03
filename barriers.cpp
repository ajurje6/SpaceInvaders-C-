#include "barriers.hpp"
Barrier::Barrier(Vector2 position) {
	this->position = position;
}
void Barrier::DrawBarrier() {
	DrawRectangle(position.x, position.y, 3, 3, RED);
}

Rectangle Barrier::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}
