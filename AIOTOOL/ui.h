#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "framework.h"

namespace ImGui {
	bool ToggleButton(const char* label, bool* v, const ImVec2& size_arg = ImVec2(0, 0));
	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool BeginGroupBox(const char* name, const ImVec2& size_arg = ImVec2(0, 0));
	void EndGroupBox();
	bool Hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0, 0));
	bool ListBox(const char* label, int* current_item, std::string items[], int items_count, int height_items);
	bool ListBox(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items);
	bool Combo(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items);
	bool Tab(const char* label, const bool selected, const ImVec2& size_arg);
}
