#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>
using namespace std;
class Spaceship{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void Reset();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        Rectangle getRect();
        vector<Laser>lasers;
    private:
        Texture2D image;
        Vector2 position;
        double FireTime;
        Sound laserSound;
};