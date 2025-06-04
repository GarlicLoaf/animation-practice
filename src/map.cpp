#include "map.h"

#include <raymath.h>

#include <algorithm>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

const std::string ldtk_path = std::string(RESOURCES_PATH) + "map/";

Texture2D LoadTexture(const json* layer) {
    std::string texture_path;
    texture_path = (*layer)["__tilesetRelPath"];
    return (LoadTexture(
        (std::string(RESOURCES_PATH) + "map/" + texture_path).c_str()));
}

Map LoadMap() {
    // json initialization
    json map_data;

    std::fstream File;
    File.open(ldtk_path + "map.ldtk", std::ios::in);
    if (!File.is_open()) {
        std::cerr << "Error: Could not open json file at "
                  << ldtk_path + "map.ldtk" << "\n";
        return {};
    }

    try {
        File >> map_data;
    } catch (const json::parse_error& e) {
        std::cerr << "Error: Failed to parse the JSON file. " << e.what()
                  << std::endl;
        return {};
    }

    // initialize the map struct
    Map map{};

    for (const auto& layer : map_data["levels"][0]["layerInstances"]) {
        std::string layer_type = layer["__type"];

        Layer map_layer{};
        map_layer.name = layer["__identifier"];

        if (layer_type == "Entities") {
            map_layer.type = ENTITY_LAYER;
            for (const auto& instance : layer["entityInstances"]) {
                std::string dialogue_name =
                    instance["fieldInstances"][0]["__value"];
                map_layer.tile_information.push_back(dialogue_name);

                float tile_x = instance["__grid"][0];
                float tile_y = instance["__grid"][1];
                map_layer.tile_positions.push_back(Vector2{tile_x, tile_y});
            }

        } else if (layer_type == "IntGrid") {
            if (layer["__tilesetDefUid"] != nullptr) {
                map_layer.type = AUTO_LAYER;
                map_layer.texture = LoadTexture(&layer);

                for (const auto& tile : layer["autoLayerTiles"]) {
                    float px_x = tile["px"][0];
                    float px_y = tile["px"][1];

                    float src_x = tile["src"][0];
                    float src_y = tile["src"][1];

                    map_layer.tile_positions.push_back(Vector2{px_x, px_y});
                    map_layer.src_positions.push_back(Vector2{src_x, src_y});
                }
            } else {
                map_layer.type = COLLISION_LAYER;
                int map_width = layer["__cWid"].get<int>();
                int map_height = layer["__cHei"].get<int>();

                for (int i{0}; i < map_width * map_height; i++) {
                    int tile_type = layer["intGridCsv"][i];

                    float x = i % map_width;
                    float y = i / map_width;

                    if (tile_type == 1) {
                        map_layer.tile_positions.push_back(Vector2{x, y});
                    }
                }
            }

        } else if (layer_type == "Tiles") {
            map_layer.type = TILE_LAYER;
            map_layer.texture = LoadTexture(&layer);

            for (const auto& tile : layer["gridTiles"]) {
                float px_x = tile["px"][0];
                float px_y = tile["px"][1];

                float src_x = tile["src"][0];
                float src_y = tile["src"][1];

                map_layer.tile_positions.push_back(Vector2{px_x, px_y});
                map_layer.src_positions.push_back(Vector2{src_x, src_y});
            }
        }
        map.layers.push_back(map_layer);
    }
    // this is just quick and dirty to allow for push_back
    // it doesn't affect performance as it is just done once at map parse time
    std::reverse(map.layers.begin(), map.layers.end());
    TraceLog(LOG_DEBUG, "UPDATE: Parsed map successfully");
    return map;
}

void DrawMap(Map* map_data, Vector2* player_position) {
    Rectangle src{0.0f, 0.0f, 16.0f, 16.0f};
    Rectangle target{0.0f, 0.0f, 64.0f, 64.0f};
    Vector2 player_offset = Vector2Subtract(
        Vector2Scale(*player_position, 64.0f), Vector2{256.0f, 256.0f});

    for (auto layer : map_data->layers) {
        if (layer.type == AUTO_LAYER || layer.type == TILE_LAYER) {
            for (int i{0}; i < layer.tile_positions.size(); i++) {
                src.x = layer.src_positions[i].x;
                src.y = layer.src_positions[i].y;

                target.x = layer.tile_positions[i].x * 4.0f;
                target.y = layer.tile_positions[i].y * 4.0f;

                DrawTexturePro(layer.texture, src, target, player_offset, 0.0f,
                               WHITE);
            }
        }
    }
}

void UnloadMap(Map* map_data) {
    for (auto layer : map_data->layers) {
        UnloadTexture(layer.texture);
    }
}
