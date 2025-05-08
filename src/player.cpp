#include "player.h"

#include <algorithm>
#include <iostream>

#include "raymath.h"

void PlayerInput(Player *player,
                 const std::vector<CollisionTile> *collision_vector) {
    if (IsKeyPressed(KEY_W)) {
        player->direction.y = -1.0f;
    } else if (IsKeyPressed(KEY_S)) {
        player->direction.y = 1.0f;
    } else if (IsKeyPressed(KEY_A)) {
        player->direction.x = -1.0f;
    } else if (IsKeyPressed(KEY_D)) {
        player->direction.x = 1.0f;
    } else {
        player->direction = Vector2{0.0f, 0.0f};
    }

    Vector2 new_grid_position{
        Vector2Add(player->grid_position, player->direction)};

    auto it =
        std::find_if(collision_vector->begin(), collision_vector->end(),
                     [&](const CollisionTile &ct) {
                         return ct.grid_position.x == new_grid_position.x &&
                                ct.grid_position.y == new_grid_position.y &&
                                ct.tile_type == 1;
                     }
        );

    if (it != collision_vector->end()) {
    } else {
        player->position = Vector2Add(player->position,
                                      Vector2Scale(player->direction, 16.0f));
        player->grid_position = new_grid_position;
    }
}

void DrawPlayer(Player *player, const Texture2D *texture) {
    Rectangle rect{8.0f, 13.0f, 16.0f, 16.0f};

    Rectangle target{player->position.x * 4, player->position.y * 4, 64.0f,
                     64.0f};

    DrawTexturePro(*texture, rect, target, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}
