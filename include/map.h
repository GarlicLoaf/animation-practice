#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "raylib.h"

using json = nlohmann::json;

enum LayerType { ENTITY_LAYER, COLLISION_LAYER, TILE_LAYER, AUTO_LAYER };

typedef struct Layer {
    LayerType type;
    std::string name;
    std::vector<Vector2> src_positions;
    std::vector<Vector2> tile_positions;
    std::vector<std::string> tile_information;
    Texture2D texture;
} Layer;

typedef struct Map {
    int width;
    int height;
    Vector2 origin;
    Vector2 spawn;
    std::vector<Layer> layers;
} Map;

Map LoadMap();

void DrawMap(Map* map_data, Vector2* player_position);

void UnloadMap(Map* map_data);
