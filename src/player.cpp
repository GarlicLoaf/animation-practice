#include "player.h"

#include <algorithm>
#include <iostream>

#include "raymath.h"

void PlayerInput(Player *player,
                 const std::vector<CollisionTile> *collision_vector) {
    switch (player->state) {
        case WALKING: {
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

            auto it = std::find_if(
                collision_vector->begin(), collision_vector->end(),
                [&](const CollisionTile &ct) {
                    return ct.grid_position.x == new_grid_position.x &&
                           ct.grid_position.y == new_grid_position.y;
                });

            if (it != collision_vector->end()) {
                int tile_type = it->tile_type;

                if (tile_type == 1) {
                } else if (tile_type == 2) {
                    // player comes across a dialogue box
                    player->state = READING;
                    LoadDialogue(&player->dialogue);
                }
            } else {
                player->grid_position = new_grid_position;
            }
            break;
        }
        case READING: {
            break;
        }
    }
}

void DrawPlayer(Player *player, const Texture2D *texture) {
    // Always draws the player in the center of the screen, regardless of
    // player.grid_position
    Rectangle rect{8.0f, 13.0f, 16.0f, 16.0f};

    Rectangle target{256.0f, 256.0f, 64.0f, 64.0f};

    DrawTexturePro(*texture, rect, target, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}
