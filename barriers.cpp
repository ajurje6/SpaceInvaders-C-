#include "barriers.hpp"
Barrier::Barrier(Vector2 position) {
	this->position = position;
}
void Barrier::DrawBarrier() {
	DrawRectangle(position.x, position.y, 3, 3, RED);
}