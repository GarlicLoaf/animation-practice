#include "map.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

void ParseMap() {
    // json initialization
    json LDTK;
    std::string json_path =
        std::string(RESOURCES_PATH) + "map/map/simplified/Level_0/data.json";
    std::fstream File;
    File.open(json_path, std::ios::in);

    json MapData{json::parse(File)};

    std::cout << MapData.dump(2);
}
