#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
class Game {
    public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    int lives;
    int score;
    bool isRunning;
    Music music;
    private:
        void DeleteDeactivatedLasers();
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        void DropAliensDown(int distance);
        void AlienFire();
        void CheckCollision();
        void GameOver();
        void Restart();
        void GameInitialization();
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        int aliensDirection;
        std::vector<Laser> alienLasers;
       constexpr static float alienLaserDuration = 0.4;
       float alienLastFiredLaser;
       MysteryShip mysteryShip;
       float mysteryShipSpawnInterval;
       float lastSpawned;
       Sound explosionSound;
};