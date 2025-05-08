#include "map.h"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

const std::string ldtk_path = std::string(RESOURCES_PATH) + "map/";

Map ParseMap() {
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

    TraceLog(LOG_DEBUG, "UPDATE: Parsed map successfully");

    // initialize the map struct
    Map map{};
    map.origin = Vector2{0.0f, 0.0f};

    for (const auto& layer : map_data["levels"][0]["layerInstances"]) {
        // handle background tile info
        if (layer["iid"].get<std::string>() ==
            "dd6d11d0-1030-11f0-b004-819f6d3e2371") {
            for (const auto& tile : layer["gridTiles"]) {
                float px_x = tile["px"][0].get<float>();
                float px_y = tile["px"][1].get<float>();

                float src_x = tile["src"][0].get<float>();
                float src_y = tile["src"][1].get<float>();

                map.background_pos.push_back(Vector2{px_x, px_y});
                map.background_src_pos.push_back(Vector2{src_x, src_y});
            }
        }
        // handle collision info
        else if (layer["iid"].get<std::string>() ==
                 "fcae4de0-1030-11f0-a23a-b9b8d00d2e67") {
            // don't handle this for now
        }
    }

    return map;
}

void DrawMap(const Map* map_data, const Texture2D* tileset) {
    Rectangle src{0.0f, 0.0f, 16.0f, 16.0f};
    Rectangle target{0.0f, 0.0f, 64.0f, 64.0f};

    for (int i{0}; i < map_data->background_pos.size(); i++) {
        src.x = map_data->background_src_pos[i].x;
        src.y = map_data->background_src_pos[i].y;

        target.x = map_data->background_pos[i].x * 4.0f;
        target.y = map_data->background_pos[i].y * 4.0f;

        DrawTexturePro(*tileset, src, target, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    }
}
