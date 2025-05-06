#include <iostream>
#include <string>

#include "map.h"
#include "raylib.h"

typedef struct Animation {
    Vector2 root;
    int fps;
    int frames;
    int current_frame;
} Animation;

int main() {
    InitWindow(500, 500, "Testing Stuff");
    SetTargetFPS(30);

    // ressource allocation
    std::string player_texture_path = std::string(RESOURCES_PATH) + "chars.png";
    const Texture2D player_texture = LoadTexture(player_texture_path.c_str());

    int frame_counter{0};

    ParseMap();

    while (!WindowShouldClose()) {
        // update step
        frame_counter++;

        if (frame_counter >= 30) {
            frame_counter = 0;
        }

        // drawing step
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    // ressource deallocation
    UnloadTexture(player_texture);
    CloseWindow();
    return 0;
}
