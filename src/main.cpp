#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "dialogue.h"
#include "globals.h"
#include "map.h"
#include "player.h"
#include "raylib.h"

using json = nlohmann::json;

typedef struct Animation {
    Vector2 root;
    int fps;
    int frames;
    int current_frame;
} Animation;

int main() {
    InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    SetTraceLogLevel(2);

    // ressource allocation
    std::string player_texture_path = std::string(RESOURCES_PATH) + "chars.png";
    const Texture2D player_texture = LoadTexture(player_texture_path.c_str());

    std::string map_texture_path =
        std::string(RESOURCES_PATH) + "map/CastleTown_A.png";
    const Texture2D map_texture = LoadTexture(map_texture_path.c_str());

    const Map map_data{ParseMap()};

    // initialize player
    Dialogue dialogue{{}, 0};
    Player player{Vector2{0.0f, 0.0f}, Vector2{15.0f, 15.0f}, false, WALKING,
                  dialogue};

    while (!WindowShouldClose()) {
        // update step
        PlayerInput(&player, &map_data.collision);

        if (player.state == READING) {
        }

        // drawing step
        BeginDrawing();
        ClearBackground(BLACK);

        DrawMap(&map_data, &map_texture, &player.grid_position);
        DrawPlayer(&player, &player_texture);

        DrawText(TextFormat("Grid Position: %.2f, %.2f", player.grid_position.x,
                            player.grid_position.y),
                 0, 0, 20, WHITE);

        if (player.state == READING) {
            DrawDialogue(&player.dialogue);
        }
        EndDrawing();
    }

    // ressource deallocation
    UnloadTexture(player_texture);
    UnloadTexture(map_texture);

    CloseWindow();
    return 0;
}
