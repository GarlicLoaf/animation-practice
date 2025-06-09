#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "animation.h"
#include "dialogue.h"
#include "globals.h"
#include "map.h"
#include "player.h"
#include "raylib.h"

using json = nlohmann::json;

int main() {
    InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    SetTraceLogLevel(4);

    // ressource allocation
    std::string player_texture_path =
        std::string(RESOURCES_PATH) + "character.png";
    const Texture2D player_texture = LoadTexture(player_texture_path.c_str());

    Map map_data{LoadMap()};

    // initialize player
    Dialogue dialogue{{}, 0};
    Animation player_animation{0, 2, 0, 0, 0.3, 0.3};
    Player player{Vector2{0.0f, 0.0f},
                  Vector2{15.0f, 15.0f},
                  Vector2{15.0f, 15.0f},
                  IDLE,
                  dialogue,
                  player_animation};

    while (!WindowShouldClose()) {
        // update step
        PlayerInput(&player, &map_data.layers[0], &map_data.layers[1]);

        // drawing step
        BeginDrawing();
        ClearBackground(BLACK);

        DrawMap(&map_data, &player.grid_position);
        DrawPlayer(&player, &player_texture);

        DrawText(TextFormat("Grid Position: %.2f, %.2f", player.grid_position.x,
                            player.grid_position.y),
                 0, 0, 20, WHITE);

        if (player.state == READING) {
            DrawDialogue(&player.dialogue);
        }
        EndDrawing();
    }

    UnloadMap(&map_data);
    UnloadTexture(player_texture);

    CloseWindow();
    return 0;
}
