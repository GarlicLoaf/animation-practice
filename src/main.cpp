#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

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
    InitWindow(144 * 4, 112 * 4, "Testing Stuff");
    SetTargetFPS(30);

    SetTraceLogLevel(2);

    // ressource allocation
    std::string player_texture_path = std::string(RESOURCES_PATH) + "chars.png";
    const Texture2D player_texture = LoadTexture(player_texture_path.c_str());

    std::string map_texture_path =
        std::string(RESOURCES_PATH) + "map/AdventureBegins_Demo.png";
    const Texture2D map_texture = LoadTexture(map_texture_path.c_str());

    const Map map_data{ParseMap()};

    // initialize player
    Player player{Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f}, false};

    while (!WindowShouldClose()) {
        // update step
        PlayerInput(&player, &map_data.collision);

        // drawing step
        BeginDrawing();
        ClearBackground(BLACK);

        DrawMap(&map_data, &map_texture);
        DrawPlayer(&player, &player_texture);

        EndDrawing();
    }

    // ressource deallocation
    UnloadTexture(player_texture);
    UnloadTexture(map_texture);

    CloseWindow();
    return 0;
}
