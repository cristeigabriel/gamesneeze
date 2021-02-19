#include "imgui/imgui.h"
#include "menu.hpp"
#include <SDL2/SDL_keyboard.h>

void Menu::CustomWidgets::drawKeyBinder(const char* label, int* key, bool* toggled) {
    //Create label
    char l[64];
    if (*toggled) {
        snprintf(l, sizeof(l), "Press a key...");
    } else {
        snprintf(l, sizeof(l), "%s: %s", label, (*key >= 0) ? SDL_GetKeyName(SDL_GetKeyFromScancode((SDL_Scancode) *key)) :
                                                (*key == -1) ? "Mouse1" : 
                                                (*key == -2) ? "Mouse2" :
                                                (*key == -3) ? "Mouse3" : "");
    }

    // Draw button
    if (ImGui::Button(l)) {
        *toggled = !*toggled;
    };

    // Handle KeyPresses
    if (ImGui::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
        *key = 0;
        *toggled = false;
    }

    if (*toggled) {
        for (auto i = 0; i < SDL_NUM_SCANCODES; i++) {
            if (ImGui::IsKeyPressed(i)) {
                *key = i;
                *toggled = false;
            }
        }
        if (ImGui::IsMouseDown(0)) {
            *key = -1;
            *toggled = false;
        }
        if (ImGui::IsMouseDown(1)) {
            *key = -2;
            *toggled = false;
        }
        if (ImGui::IsMouseDown(2)) {
            *key = -3;
            *toggled = false;
        }
        // TODO: Mouse4 & Mouse5
    }
}

bool Menu::CustomWidgets::isKeyDown(int key) {
    if (key > 0) {
        return ImGui::IsKeyDown(key);
    }
    switch(key) {
        case -1: return ImGui::IsMouseDown(0);
        case -2: return ImGui::IsMouseDown(1);
        case -3: return ImGui::IsMouseDown(2);
    }
    return 0;
}