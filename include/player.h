#pragma once

#include <vector>

#include "raylib.h"

struct Player {
    Vector2 position;
    Vector2 direction;
    Vector2 grid_position;
    bool is_moving;
};

void PlayerInput(Player *player, const std::vector<int> *collision_vector);
void DrawPlayer(Player *player, const Texture2D *texture);
