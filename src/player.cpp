#include "player.h"

#include "raymath.h"

void PlayerInput(Player *player, const std::vector<int> *collision_vector) {
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

    player->position = Vector2Add(player->position, Vector2Scale(player->direction, 16.0f));
}

void DrawPlayer(Player *player, const Texture2D *texture) {
    Rectangle rect{8.0f, 13.0f, 16.0f, 16.0f};

    Rectangle target{player->position.x * 4, player->position.y * 4, 64.0f,
                     64.0f};

    DrawTexturePro(*texture, rect, target, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}
