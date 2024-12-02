#pragma once
#include <vector>
#include "barriers.hpp"
class Obstacle {
public:
    Obstacle(Vector2 position);
    void DrawObstacle();
    Vector2 position;
    std::vector<Barrier> barriers;
    static std::vector<std::vector<int>> grid;
private:
};