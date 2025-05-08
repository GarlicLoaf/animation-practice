#pragma once

#include <nlohmann/json.hpp>
#include <vector>

#include "raylib.h"

using json = nlohmann::json;

typedef struct CollisionTile {
    Vector2 grid_position;
    int tile_type;
} CollisionTile;

typedef struct Map {
    int width;
    int height;
    Vector2 origin;
    Vector2 spawn;
    std::vector<CollisionTile> collision;
    std::vector<Vector2> background_pos;
    std::vector<Vector2> background_src_pos;
} Map;

Map ParseMap();

void DrawMap(const Map *map_data, const Texture2D *tileset);
