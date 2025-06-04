#include "dialogue.h"

#include <raymath.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "globals.h"

void LoadDialogue(Dialogue* dialogue, std::string* path) {
    std::fstream File;
    std::string dialogue_path = std::string(RESOURCES_PATH) + *path + ".json";
    File.open(dialogue_path.c_str(), std::ios::in);
    if (!File.is_open()) {
        std::cerr << "Error: Could not open json file at " << dialogue_path
                  << "\n";
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

void DrawText(Vector2* print_position, std::istringstream* iss, Color color) {
    std::string word{};

    while (*iss >> word) {
        int word_width = MeasureText(word.c_str(), TEXT_SIZE);
        int space_width = MeasureText(" ", TEXT_SIZE);

        int remaining_space = SCREEN_WIDTH - (print_position->x + word_width);

        if (remaining_space > 0) {
        } else {
            *print_position = Vector2{10.0f, print_position->y + TEXT_SIZE + 2};
        }
        DrawText(word.c_str(), print_position->x, print_position->y, TEXT_SIZE,
                 color);
        print_position->x += word_width + space_width * 1.5;
    }
    *print_position = Vector2{10.0f, print_position->y + TEXT_SIZE + 2};
}

void DrawDialogue(Dialogue* dialogue) {
    auto& lines = dialogue->content["lines"];
    std::string current_line_str = std::to_string(dialogue->current_line);
    std::string current_text = lines[current_line_str]["text"];

    DrawRectangle(0, 64 * 7, 64 * 9, 64 * 2, BLACK);

    int text_size_left = current_text.length();
    Vector2 print_position{10.0f, 458.0f};

    std::istringstream iss(current_text);
    DrawText(&print_position, &iss, WHITE);

    if (lines[current_line_str]["type"] == 1) {
        print_position = Vector2Add(print_position, Vector2{0.0f, 10.0f});
        int counter = 0;
        for (const auto& decision : lines[current_line_str]["options"]) {
            Color print_color = DARKGRAY;

            std::string decision_text = lines[to_string(decision)]["text"];

            if (dialogue->current_decision == counter) {
                print_color = WHITE;
                std::string selection_symb = ">";
                decision_text = selection_symb + decision_text;
            }

            std::istringstream decision_stream(decision_text);
            DrawText(&print_position, &decision_stream, print_color);
            counter += 1;
        }
        dialogue->decision_size = counter;
    } else {
        dialogue->decision_size = 0;
        dialogue->current_decision = 0;
    }
}
