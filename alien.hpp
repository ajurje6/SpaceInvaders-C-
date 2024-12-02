#pragma once
#include <raylib.h>
class Alien {
	public:
		int typeOfAlien;
		static void UnloadImages();
		static Texture2D alienImages[3];
		Vector2 position;
		Alien(int typeOfAlien,Vector2 position);
		void DrawAlien();
		void UpdateAlien(int direction);
		int GetTypeOfAlien();
	private:
};