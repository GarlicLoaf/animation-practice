#include "dialogue.h"

#include <fstream>
#include <iostream>
#include <string>

void LoadDialogue(Dialogue* dialogue) {
    std::fstream File;
    File.open(sds_path + "", std::ios::in);
    if (!File.is_open()) {
        std::cerr << "Error: Could not open json file at " << sds_path << "\n";
        return;
    }

    try {
        File >> dialogue->content;
    } catch (const json::parse_error& e) {
        std::cerr << "Error: Failed to parse the JSON file. " << e.what()
                  << std::endl;
        return;
    }
    TraceLog(LOG_DEBUG, "UPDATE: Loaded dialogue successfully");
    return;
}

void UnloadDialogue(Dialogue* dialogue) {
    dialogue->content = {};
    dialogue->current_line = 0;
}

void DrawDialogue(Dialogue* dialogue) {
    const std::string& line_string =
        dialogue
            ->content["lines"][std::to_string(dialogue->current_line)]["text"];

    DrawText(line_string.c_str(), 0, 400, 30, BLACK);
}
