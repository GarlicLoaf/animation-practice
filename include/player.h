#pragma once

#include <vector>

#include "dialogue.h"
#include "map.h"
#include "raylib.h"

enum PLAYER_STATE { WALKING, READING };

struct Player {
    Vector2 direction;
    Vector2 grid_position;
    bool is_moving;
    PLAYER_STATE state;
    Dialogue dialogue;
};

void PlayerInput(Player *player);
void DrawPlayer(Player *player, const Texture2D *texture);
