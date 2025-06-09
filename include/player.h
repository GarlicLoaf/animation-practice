#pragma once

#include <vector>

#include "dialogue.h"
#include "map.h"
#include "raylib.h"

enum PLAYER_STATE { IDLE, WALKING, READING };

struct Player {
    Vector2 direction;
    Vector2 grid_position;
    Vector2 goal_position;
    PLAYER_STATE state;
    Dialogue dialogue;
};

void PlayerInput(Player *player, Layer *collision_layer, Layer *dialogue_layer);
void DrawPlayer(Player *player, const Texture2D *texture);
