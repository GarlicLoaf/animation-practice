#pragma once

#include <nlohmann/json.hpp>

#include "raylib.h"

using json = nlohmann::json;

typedef struct Dialogue {
    json content;
    int current_line;
} Dialogue;

const std::string sds_path =
    std::string(RESOURCES_PATH) + "/example_dialogue.json";

void LoadDialogue(Dialogue* dialogue);
void UnloadDialogue(Dialogue* dialogue);
void DrawDialogue(Dialogue* dialogue);
