#pragma once
#include <raylib.h>
class Barrier {
	public:
		Barrier(Vector2 position);
		void DrawBarrier();
		Rectangle getRect();
	private:
		Vector2 position;
};