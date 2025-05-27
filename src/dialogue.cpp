#include "dialogue.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "globals.h"

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
    auto& lines = dialogue->content["lines"];
    std::string current_line_str = std::to_string(dialogue->current_line);
    std::string current_text = lines[current_line_str]["text"];

    DrawRectangle(0, 64 * 7, 64 * 9, 64 * 2, BLACK);

    int text_size_left = current_text.length();
    Vector2 print_position{10.0f, 458.0f};

    std::istringstream iss(current_text);
    std::string word{};

    while (iss >> word) {
        int word_width = MeasureText(word.c_str(), TEXT_SIZE);
        int space_width = MeasureText(" ", TEXT_SIZE);

        int remaining_space = SCREEN_WIDTH - (print_position.x + word_width);

        if (remaining_space > 0) {
        } else {
            print_position = Vector2{10.0f, print_position.y + TEXT_SIZE + 2};
        }
        DrawText(word.c_str(), print_position.x, print_position.y, TEXT_SIZE,
                 WHITE);
        print_position.x += word_width + space_width * 1.5;
    }
}
