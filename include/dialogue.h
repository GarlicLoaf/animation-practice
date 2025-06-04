#pragma once

#include <nlohmann/json.hpp>

#include "raylib.h"

using json = nlohmann::json;

typedef struct Dialogue {
    json content;
    int current_line;
    int decision_size;
    int current_decision;
} Dialogue;

const std::string sds_path = std::string(RESOURCES_PATH) + "/grass.json";

void LoadDialogue(Dialogue* dialogue, std::string* path);
void UnloadDialogue(Dialogue* dialogue);
void DrawDialogue(Dialogue* dialogue);
