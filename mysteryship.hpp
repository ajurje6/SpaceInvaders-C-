#include <raylib.h>
class MysteryShip {
public:
	MysteryShip();
	~MysteryShip();
	void UpdateMysteryShip();
	void DrawMysteryShip();
	void SpawnMysteryShip();
	bool alive;
	Rectangle getRect();
private:
	Vector2 position;
	Texture2D image;
	int speed;
};