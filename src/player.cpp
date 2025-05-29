#include "player.h"

#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

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
            if (IsKeyPressed(KEY_E)) {
                auto &lines = player->dialogue.content["lines"];
                std::string current_line_str =
                    std::to_string(player->dialogue.current_line);
                auto &current_line_data = lines[current_line_str];

                if (current_line_data["next"] == -1) {
                    player->state = WALKING;
                    UnloadDialogue(&player->dialogue);
                    return;
                }
                if (player->dialogue.decision_size > 0) {
                    int decision =
                        current_line_data["options"]
                                         [player->dialogue.current_decision];
                    player->dialogue.current_line =
                        lines[std::to_string(decision)]["next"];

                } else {
                    player->dialogue.current_line =
                        current_line_data["next"].get<int>();
                }
            }
            if (player->dialogue.decision_size > 0) {
                if (IsKeyPressed(KEY_W)) {
                    player->dialogue.current_decision =
                        std::max(player->dialogue.current_decision - 1, 0);
                } else if (IsKeyPressed(KEY_S)) {
                    player->dialogue.current_decision =
                        std::min(player->dialogue.current_decision + 1,
                                 player->dialogue.decision_size - 1);
                }
            }
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
