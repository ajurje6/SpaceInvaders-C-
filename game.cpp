#include "game.hpp"
Game::Game() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    alienLastFiredLaser = 0.0;
}
Game::~Game() {

}
void Game::Update() {
    for (auto& laser : spaceship.lasers) {
        laser.UpdateLaser();
    }
    MoveAliens();
    AlienFire();
    for (auto& laser : alienLasers) {
        laser.UpdateLaser();
    }
    DeleteDeactivatedLasers();
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
}

void Game::HandleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    }
    else if (IsKeyDown(KEY_SPACE)|| IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        spaceship.FireLaser();
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
        obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 135) }));
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
            float y = 35 + row * 55;    // vertical starting position
            aliens.push_back(Alien(alienType, { x, y }));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for (auto& alien : aliens) {
        //Ensures that aliens change direction when they reach end of the screen
        if (alien.position.x + alien.alienImages[alien.typeOfAlien - 1].width > GetScreenWidth()) {
            aliensDirection = -1;
            DropAliensDown(6);
        }
        if (alien.position.x < 25) {
            aliensDirection = 1;
            DropAliensDown(6);
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
    double currentTime = GetTime();
    if (currentTime - alienLastFiredLaser >= alienLaserDuration && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({
            alien.position.x + alien.alienImages[alien.typeOfAlien - 1].width / 2,
            alien.position.y + alien.alienImages[alien.typeOfAlien - 1].height
            }, 6));
        alienLastFiredLaser = GetTime();
    }
}
