#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "dialogue.h"
#include "globals.h"
#include "map.h"
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

    SetTraceLogLevel(1);

    // ressource allocation
    std::string player_texture_path =
        std::string(RESOURCES_PATH) + "character.png";
    const Texture2D player_texture = LoadTexture(player_texture_path.c_str());

    // map_textures["grass"] =
    //     LoadTexture((RESOURCES_PATH + std::string("map/Grass.png")).c_str());
    // map_textures["water"] =
    //     LoadTexture((RESOURCES_PATH + std::string("map/Water.png")).c_str());
    // map_textures["hills"] =
    //     LoadTexture((RESOURCES_PATH + std::string("map/Hills.png")).c_str());

    Map map_data{LoadMap()};

    // initialize player
    Dialogue dialogue{{}, 0};
    // Player player{Vector2{0.0f, 0.0f}, Vector2{15.0f, 15.0f}, false, WALKING,
    //               dialogue};
    Vector2 temp_player_vec{5.0f, 5.0f};

    while (!WindowShouldClose()) {
        // update step
        // PlayerInput(&player, &map_data.collision);

        // drawing step
        BeginDrawing();
        ClearBackground(BLACK);

        DrawMap(&map_data, &temp_player_vec);
        // DrawPlayer(&player, &player_texture);

        // DrawText(TextFormat("Grid Position: %.2f, %.2f",
        // player.grid_position.x,
        //                     player.grid_position.y),
        //          0, 0, 20, WHITE);

        // if (player.state == READING) {
        //     DrawDialogue(&player.dialogue);
        // }
        EndDrawing();
    }

    UnloadMap(&map_data);
    UnloadTexture(player_texture);

    CloseWindow();
    return 0;
}
