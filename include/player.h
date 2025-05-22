#pragma once

#include <vector>

#include "map.h"
#include "raylib.h"

enum PLAYER_STATE { WALKING, READING };

struct Player {
    Vector2 direction;
    Vector2 grid_position;
    bool is_moving;
    PLAYER_STATE state;
};

void PlayerInput(Player *player,
                 const std::vector<CollisionTile> *collision_vector);
void DrawPlayer(Player *player, const Texture2D *texture);
