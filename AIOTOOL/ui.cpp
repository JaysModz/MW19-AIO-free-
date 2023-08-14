#include "ui.h"

bool ImGui::ToggleButton(const char* label, bool* v, const ImVec2& size_arg) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) return false;

	int flags = 0;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id)) return false;

	if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat) flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

	// Render
	const ImU32 col = ImGui::GetColorU32((hovered && held || *v) ? ImGuiCol_ButtonActive : (hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button));
	ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
	ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
	if (pressed) *v = !*v;

	return pressed;
}

static bool Items_ArrayGetter(void* data, int idx, const char** out_text) {
	const char* const* items = (const char* const*)data;
	if (out_text) *out_text = items[idx];
	return true;
}

static auto vector_getter = [](void* vec, int idx, const char** out_text) {
	auto& vector = *static_cast<std::vector<std::string>*>(vec);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	*out_text = vector.at(idx).c_str();
	return true;
};

bool ImGui::Combo(const char* label, int* currIndex, std::vector<std::string>& values) {
	if (values.empty()) { return false; }
	return ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
}

bool ImGui::BeginGroupBox(const char* name, const ImVec2& size_arg) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;

	window->DC.CursorPos.y += GImGui->FontSize / 2;
	const ImVec2 content_avail = ImGui::GetContentRegionAvail();
	ImVec2 size = ImFloor(size_arg);
	if (size.x <= 0.0f) {
		size.x = ImMax(content_avail.x, 4.0f) - fabsf(size.x); // Arbitrary minimum zero-ish child size of 4.0f (0.0f causing too much issues)
	}
	if (size.y <= 0.0f) {
		size.y = ImMax(content_avail.y, 4.0f) - fabsf(size.y);
	}

	ImGui::SetNextWindowSize(size);
	bool ret;
	ImGui::Begin(name, &ret, flags);
	//bool ret = ImGui::Begin(name, NULL, size, -1.0f, flags);

	window = ImGui::GetCurrentWindow();

	auto padding = ImGui::GetStyle().WindowPadding;

	auto text_size = ImGui::CalcTextSize(name, NULL, true);

	if (text_size.x > 1.0f) {
		window->DrawList->PushClipRectFullScreen();
		window->DrawList->PopClipRect();
	}

	return ret;
}

void ImGui::EndGroupBox() {
	ImGui::EndChild();
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DC.CursorPosPrevLine.y -= GImGui->FontSize / 2;
}

bool ImGui::ListBox(const char* label, int* current_item, std::string items[], int items_count, int height_items) {
	char** tmp;
	tmp = new char* [items_count];
	for (int i = 0; i < items_count; i++) {
		tmp[i] = const_cast<char*>(items[i].c_str());
	}

	const bool value_changed = ImGui::ListBox(label, current_item, Items_ArrayGetter, static_cast<void*>(tmp), items_count, height_items);
	return value_changed;
}

bool ImGui::ListBox(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items) {
	return ImGui::ListBox(label, current_item, [](void* data, int idx, const char** out_text) {
		*out_text = (*reinterpret_cast<std::function<const char* (int)>*>(data))(idx);
		return true;
		}, &lambda, items_count, height_in_items);
}

bool ImGui::Combo(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items) {
	return ImGui::Combo(label, current_item, [](void* data, int idx, const char** out_text) {
		*out_text = (*reinterpret_cast<std::function<const char* (int)>*>(data))(idx);
		return true;
		}, &lambda, items_count, height_in_items);
}

bool ImGui::Tab(const char* label, const bool selected, const ImVec2& size_arg) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;

	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

	if (selected)
		window->DrawList->AddRectFilled({ bb.Min.x + 20,bb.Max.y - 7 }, { bb.Max.x - 20, bb.Max.y - 5 }, ImColor(IM_COL32_WHITE), 6);

	window->DrawList->AddText(ImVec2(bb.Min.x + size_arg.x / 2 - ImGui::CalcTextSize(label).x / 2, bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2),
		ImColor(IM_COL32_WHITE), label);

	return pressed;
}