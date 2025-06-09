#include "player.h"

#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "raymath.h"

void PlayerInput(Player *player, Layer *collision_layer,
                 Layer *dialogue_layer) {
    switch (player->state) {
        case IDLE: {
            player->direction = Vector2{0.0f, 0.0f};

            if (IsKeyDown(KEY_W)) {
                player->direction.y = -1.0f;
            } else if (IsKeyDown(KEY_S)) {
                player->direction.y = 1.0f;
            } else if (IsKeyDown(KEY_A)) {
                player->direction.x = -1.0f;
            } else if (IsKeyDown(KEY_D)) {
                player->direction.x = 1.0f;
            }
            Vector2 new_grid_position{
                Vector2Add(player->grid_position, player->direction)};

            auto collision =
                std::find_if(collision_layer->tile_positions.begin(),
                             collision_layer->tile_positions.end(),
                             [&new_grid_position](const Vector2 &v) {
                                 return v == new_grid_position;
                             });

            if (collision != collision_layer->tile_positions.end()) {
                // found collision, so now look for whether the tile is also a
                // dialogue box
                auto dialogue =
                    std::find_if(dialogue_layer->tile_positions.begin(),
                                 dialogue_layer->tile_positions.end(),
                                 [&new_grid_position](const Vector2 &v) {
                                     return v == new_grid_position;
                                 });
                if (dialogue != dialogue_layer->tile_positions.end()) {
                    size_t dialogue_index = std::distance(
                        dialogue_layer->tile_positions.begin(), dialogue);
                    player->state = READING;
                    LoadDialogue(
                        &player->dialogue,
                        &(dialogue_layer->tile_information[dialogue_index]));
                }
            } else {
                player->state = WALKING;
                player->goal_position = new_grid_position;
            }
            break;
        }
        case WALKING: {
            player->grid_position = Vector2Add(
                player->grid_position, Vector2Scale(player->direction, 0.05f));

            if (Vector2Distance(player->grid_position, player->goal_position) <
                0.05f) {
                player->grid_position = player->goal_position;
                player->state = IDLE;
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
                    player->state = IDLE;
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
    Rectangle rect{16.0f, 16.0f, 16.0f, 16.0f};

    Rectangle target{256.0f, 256.0f, 64.0f, 64.0f};

    DrawTexturePro(*texture, rect, target, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}
