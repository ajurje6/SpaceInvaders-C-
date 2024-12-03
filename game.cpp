#include "game.hpp"
#include <iostream>
Game::Game() {
    music = LoadMusicStream("Music/music.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    GameInitialization();
}
Game::~Game() {
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}
void Game::Update() {
    if (isRunning) {
        double currentTime = GetTime();
        if (currentTime - lastSpawned > mysteryShipSpawnInterval) {
            mysteryShip.SpawnMysteryShip();
            lastSpawned = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }
        for (auto& laser : spaceship.lasers) {
            laser.UpdateLaser();
        }
        MoveAliens();
        AlienFire();
        for (auto& laser : alienLasers) {
            laser.UpdateLaser();
        }
        DeleteDeactivatedLasers();
        mysteryShip.UpdateMysteryShip();
        CheckCollision();
    }
    else {
        if (IsKeyDown(KEY_ENTER)) {
            Restart();
            GameInitialization();
       }
    }
}

void Game::Draw() {
    spaceship.Draw();
    for (auto& laser : spaceship.lasers) {
        laser.DrawLaser();
    }
    for (auto& obstacle : obstacles) {
        obstacle.DrawObstacle();
    }
    for (auto& alien : aliens) {
        alien.DrawAlien();
    }
    for (auto& laser : alienLasers) {
        laser.DrawLaser();
    }
    mysteryShip.DrawMysteryShip();
}

void Game::HandleInput() {
    if (isRunning) {
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        }
        else if (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            spaceship.FireLaser();
        }
    } 
}

void Game::DeleteDeactivatedLasers() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->IsActive) {
            it = spaceship.lasers.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->IsActive) {
            it = alienLasers.erase(it);
        }
        else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    //calculates the width of a single obstacle by multiplying the number of grid cells
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
    //loop creates 4 obstacles
    for (int i = 0; i < 4; i++) {
        // Calculate the x-offset for each obstacle.
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 200) }));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {

            int alienType;
            if (row == 0) {
                alienType = 3;
            }
            else if (row == 1 || row == 2) {
                alienType = 2;
            }
            else {
                alienType = 1;
            }

            float x = 200 + column * 55;  // Horizontal spacing
            float y = 105 + row * 55;    // vertical starting position
            aliens.push_back(Alien(alienType, { x, y }));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for (auto& alien : aliens) {
        //Ensures that aliens change direction when they reach end of the screen
        if (alien.position.x + alien.alienImages[alien.typeOfAlien - 1].width > GetScreenWidth()-10) {
            aliensDirection = -2;
            DropAliensDown(7);
        }
        if (alien.position.x < 10) {
            aliensDirection = 2;
            DropAliensDown(7);
        }

        alien.UpdateAlien(aliensDirection);
    }
}

void Game::DropAliensDown(int distance)
{ //Drops aliens down everytime they reach end of the screen
    for (auto& alien : aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienFire()
{
    // Checks if enough time has passed since the last alien fired a lase
    double currentTime = GetTime();
    if (currentTime - alienLastFiredLaser >= alienLaserDuration && !aliens.empty()) {
        // Randomly selects an alien from the active aliens
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        // Creates a new laser at the alien's position and pushes it into the alienLasers vector
        alienLasers.push_back(Laser({
            alien.position.x + alien.alienImages[alien.typeOfAlien - 1].width / 2,
            alien.position.y + alien.alienImages[alien.typeOfAlien - 1].height
            }, 6));
        alienLastFiredLaser = GetTime();
    }
}

void Game::CheckCollision()
{
    //Spaceship lasers collision with aliens
    for (auto& laser : spaceship.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                PlaySound(explosionSound);
                if (it->typeOfAlien == 1) {
                    score += 100;
                }
                else if (it->typeOfAlien == 2) {
                    score += 200;
                }
                else if (it->typeOfAlien == 3) {
                    score += 300;
                }
                it = aliens.erase(it);
                laser.IsActive = false;
            }
            else {
                ++it; //Move to the next alien
            }
        }

        //Spaceship lasers collision with obstacles(barriers)
        for (auto& obstacle : obstacles) {
            auto it = obstacle.barriers.begin();
            while (it != obstacle.barriers.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.barriers.erase(it);
                    laser.IsActive = false;
                }
                else {
                    ++it; //Move to the next barrier
                }
            }
        }
    
        //Spaceship lasers collision with mysteryship
        if (CheckCollisionRecs(mysteryShip.getRect(), laser.getRect())) {
            mysteryShip.alive = false;
            laser.IsActive = false;
            score += 500;
        }
        //Ending of code for spaceship lasers
    }

    //Alien lasers collision with spaceship

    for (auto& laser : alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.IsActive = false;
            lives--;
            if (lives == 0) {
                GameOver();
            }
        }

        for (auto& obstacle : obstacles) {
            auto it = obstacle.barriers.begin();
            while (it != obstacle.barriers.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.barriers.erase(it);
                    laser.IsActive = false;
                }
                else {
                    ++it; //Move to the next barrier
                }
            }
        }
    }

    //Alien Collision with obstacle(barrier)

    for (auto& alien : aliens) {
        for (auto& obstacle : obstacles) {
            auto it = obstacle.barriers.begin();
            while (it != obstacle.barriers.end()) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it = obstacle.barriers.erase(it);
                }
                else {
                    it++; //Move to the next barrier
                }
            }
        }

        
    }

}

void Game::GameOver()
{
    isRunning = false;
}

void Game::Restart()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::GameInitialization()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 2;
    lives = 3;
    score = 0;
    isRunning = true;
    alienLastFiredLaser = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
}
