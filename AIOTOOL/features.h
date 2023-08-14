#pragma once
#include <string>
#include <vector>
#include <functional>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "xorstr.hpp"
#include "sdk.h"
#include "menu.h"
#include "color.h"
#include "imguipp_v2.h"
#include "sdk.cpp"
#include "imgui_knobs.h"
#include "font_awesome_6.h"
#include "font_awesome_5.h"
#include "Awesome.h"
#include "Awesome_Light.h"

using namespace std;

ImGuiWindowFlags windowFlagsChild = 0;

#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

ImFont* FA;
ImFont* FA2;
ImFont* Header;
ImFont* Header2;
ImFont* Body;
ImFont* Body2;
int iTab = 0;
bool bExit = false;
bool ShowMenu = true;
int iScreenWidth = NULL;
int iScreenHeight = NULL;
static char operator_skin[128] = "";
float fontSize = 18.f;
char cLoadoutEditorBuf[128] = " Enter Loadout Name";
char cCustomClanTagBuf[128] = " Custom Clan Tag";

namespace ImGui
{
	void unlock()
	{
		uintptr_t num = (JaysModz->baseModule + JaysModz->goffsets.unlock_offsets + 0xC);
		int num2 = mem::readMemory<int>(num);

		uintptr_t unlock_base = num + num2 + 4 - JaysModz->baseModule;
		uintptr_t numP = (JaysModz->baseModule + unlock_base + 0x60);

		memcpy((BYTE*)numP, (BYTE*)xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x30\x48\x8B\x74\x24\x38\x48\x83\xC4\x20\x5F\x48\xC7\xC0\x01\x00\x00\x00\xC3"), 28);
		mem::writeMemory<uintptr_t>(JaysModz->baseModule + unlock_base + 8, numP);
		mem::writeMemory<uintptr_t>(JaysModz->baseModule + unlock_base, JaysModz->baseModule + unlock_base);
	}
	static ImVec4 active = ImVec4(ImColor(0, 68, 170, 255));
	static ImVec4 inactive = ImVec4(ImColor(255, 255, 255, 255));
	static ImVec4 PurpleText = ImVec4(ImColor(43, 22, 43, 255));
	static ImVec4 PurpleColor = ImVec4(ImColor(43, 22, 43, 255));
	ImVec4 player_colorVec44 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4 item_colorVec44 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImColor WhiteText = ImColor(255, 255, 255);


	void SCP(int xPos, int yPos)
	{
		ImGui::SetCursorPos(ImVec2(xPos, yPos));
	}

	void SCPX(int xPos)
	{
		ImGui::SetCursorPosX(xPos);
	}

	void SCPY(int yPos)
	{
		ImGui::SetCursorPosY(yPos);
	}

	void Line(int newId)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void HoroizontalLine(int newId, int sizeX, int sizeY, int xPos, int yPos)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::SCP(xPos, yPos);
		{
			ImGui::BeginChild(id.c_str(), ImVec2(sizeX, sizeY), true);
			ImGui::EndChild();
		}
	}

	void HoroizontalLineNL(int newId, int sizeX, int sizeY, int xPos, BOOL newLine)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::SCPX(xPos);
		{
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, sizeY);
			ImGui::BeginChild(id.c_str(), ImVec2(sizeX, 1), true);
			ImGui::EndChild();
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void VerticalLine(int newId, int sizeX, int xPos, int yPos)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::SCP(xPos, yPos);
		{
			ImGui::BeginChild(id.c_str(), ImVec2(sizeX, ImGui::GetContentRegionAvail().y), true);
			ImGui::EndChild();
		}
	}

	void SliderIntNL(const char* featureName, int* featureInt, bool* featureBool, int min, int max, int size, BOOL sameLine, BOOL newLine)
	{
		ImGui::PushItemWidth(size);
		if (ImGui::SliderInt(featureName, featureInt, min, max))
		{
			*featureBool = true;
		}
		ImGui::PopItemWidth();

		if (sameLine)
		{
			ImGui::SameLine();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void VerticalLineCustom(int newId, int sizeY, int xPos, int yPos)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::SCP(xPos, yPos);
		{
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::BeginChild(id.c_str(), ImVec2(1, sizeY), true);
			ImGui::EndChild();
			ImGui::PopStyleColor();
		}
	}

	void CenterText(const char* text, int lineId, BOOL separator, BOOL newLine)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (separator)
		{
			ImGui::NewLine();
			Line(lineId);
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void CenterTextSCP(const char* text, int yPos)
	{
		ImGui::SCPY(yPos);
		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();
	}

	void CenterTextEx(const char* text, float width, int lineId, BOOL separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (separator)
			Line(lineId);
	}

	void TextNL(const char* text, BOOL newLine)
	{
		ImGui::Text(text);

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSL(const char* text, BOOL sameLine, BOOL newLine)
	{
		ImGui::Text(text);

		if (sameLine)
		{
			ImGui::SameLine();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSCP(const char* text, int x, int y)
	{
		ImGui::SCP(x, y);
		ImGui::Text(text);
	}

	void CheckBoxSCP(const char* featureName, bool* featureBool, ImVec2 pos)
	{
		ImGui::SetCursorPos(pos);
		ImGui::Checkbox(featureName, featureBool);
	}

	void CheckBoxNL(const char* featureName, bool* featureBool, BOOL newLine)
	{
		ImGui::Checkbox(featureName, featureBool);
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSL(const char* buttonName, bool* featureBool, int pos, ImVec2 size, BOOL sameLine, BOOL newLine)
	{
		ImGui::SCPX(pos);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}

		if (sameLine)
		{
			ImGui::SameLine();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSCP(const char* buttonName, bool* featureBool, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SetCursorPos(pos);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonNL(const char* buttonName, bool* featureBool, int pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCPX(pos);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = true;
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSwitchSCP(const char* buttonName, bool* featureBool, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SetCursorPos(pos);
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = !*featureBool;
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonPageSCP(const char* buttonName, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SetCursorPos(pos);
		ImGui::PushStyleColor(ImGuiCol_Button, iTab == pageNumber ? active : inactive);
		if (ImGui::Button(buttonName, size))
		{
			*page = pageNumber;
		}
		ImGui::PopStyleColor();

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void SliderIntSCP(const char* featureName, int* featureInt, int min, int max, ImVec2 pos, int size, BOOL sameLine, BOOL newLine)
	{
		ImGui::SetCursorPos(pos);
		ImGui::PushItemWidth(size);
		ImGui::SliderInt(featureName, featureInt, min, max);
		ImGui::PopItemWidth();

		if (sameLine)
		{
			ImGui::SameLine();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxLoadoutNameSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cClassSelectorList[] = { " Class 1",  " Class 2", " Class 3", " Class 4", " Class 5", " Class 6", " Class 7", " Class 8", " Class 9" , " Class 10" };
		static const char* current_item = " Select Class";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cClassSelectorList); n++)
			{
				bool is_selected = (current_item == cClassSelectorList[n]);
				if (ImGui::Selectable(cClassSelectorList[n], is_selected))
					current_item = cClassSelectorList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						JaysModz->msettings.iClassNameSelection = 0;
					}
					if (n == 1)
					{
						JaysModz->msettings.iClassNameSelection = 1;
					}
					if (n == 2)
					{
						JaysModz->msettings.iClassNameSelection = 2;
					}
					if (n == 3)
					{
						JaysModz->msettings.iClassNameSelection = 3;
					}
					if (n == 4)
					{
						JaysModz->msettings.iClassNameSelection = 4;
					}
					if (n == 5)
					{
						JaysModz->msettings.iClassNameSelection = 5;
					}
					if (n == 6)
					{
						JaysModz->msettings.iClassNameSelection = 6;
					}
					if (n == 7)
					{
						JaysModz->msettings.iClassNameSelection = 7;
					}
					if (n == 8)
					{
						JaysModz->msettings.iClassNameSelection = 8;
					}
					if (n == 9)
					{
						JaysModz->msettings.iClassNameSelection = 9;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxDGLoadoutSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cClassSelectorList[] = { " Class 1",  " Class 2", " Class 3", " Class 4", " Class 5", " Class 6", " Class 7", " Class 8", " Class 9" , " Class 10" };
		static const char* current_item = " Select Class";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cClassSelectorList); n++)
			{
				bool is_selected = (current_item == cClassSelectorList[n]);
				if (ImGui::Selectable(cClassSelectorList[n], is_selected))
					current_item = cClassSelectorList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						JaysModz->msettings.iClassNameSelection = 0;
					}
					if (n == 1)
					{
						JaysModz->msettings.iClassNameSelection = 1;
					}
					if (n == 2)
					{
						JaysModz->msettings.iClassNameSelection = 2;
					}
					if (n == 3)
					{
						JaysModz->msettings.iClassNameSelection = 3;
					}
					if (n == 4)
					{
						JaysModz->msettings.iClassNameSelection = 4;
					}
					if (n == 5)
					{
						JaysModz->msettings.iClassNameSelection = 5;
					}
					if (n == 6)
					{
						JaysModz->msettings.iClassNameSelection = 6;
					}
					if (n == 7)
					{
						JaysModz->msettings.iClassNameSelection = 7;
					}
					if (n == 8)
					{
						JaysModz->msettings.iClassNameSelection = 8;
					}
					if (n == 9)
					{
						JaysModz->msettings.iClassNameSelection = 9;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxCamoLoadoutSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cCamoClassSelectorList[] = { " Loadout 1",  " Loadout 2", " Loadout 3", " Loadout 4", " Loadout 5", " Loadout 6", " Loadout 7", " Loadout 8", " Loadout 9" , " Loadout 10" };
		static const char* current_item = " Select Loadout";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cCamoClassSelectorList); n++)
			{
				bool is_selected = (current_item == cCamoClassSelectorList[n]);
				if (ImGui::Selectable(cCamoClassSelectorList[n], is_selected))
					current_item = cCamoClassSelectorList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 0;
					}
					if (n == 1)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 1;
					}
					if (n == 2)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 2;
					}
					if (n == 3)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 3;
					}
					if (n == 4)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 4;
					}
					if (n == 5)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 5;
					}
					if (n == 6)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 6;
					}
					if (n == 7)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 7;
					}
					if (n == 8)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 8;
					}
					if (n == 9)
					{
						JaysModz->msettings.iCamoLoadoutSelection = 9;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxWeaponSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cWeaponSelectorList[] = { " Primary",  " Secondary" };
		static const char* current_item = " Select Gun Slot";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cWeaponSelectorList); n++)
			{
				bool is_selected = (current_item == cWeaponSelectorList[n]);
				if (ImGui::Selectable(cWeaponSelectorList[n], is_selected))
					current_item = cWeaponSelectorList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						JaysModz->msettings.iWeaponSelection = 0;
					}
					if (n == 1)
					{
						JaysModz->msettings.iWeaponSelection = 1;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxCamoSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cCamoList[] = { " (MW) Gold", " (MW) Platinum", " (MW) Damascus", " (MW) Obsidian", " (CW) Gold", " (CW) Diamond", " (CW) DMU", " (CW) Golden Viper", " (CW) Plague Diamond", " (CW) Dark Aether", " (VG) Gold", " (VG) Diamond",
			" (VG) Atomic", " (VG) Fake Diamond", " (VG) Golden Viper", " (VG) Plague Diamond", " (VG) Dark Aether"," (CW) Cherry Blossom",  " (MW) Acticamo", " (MW) Banded"," (VG) False Prospector", " (VG) Death Prospector", " (VG) Titanium Chrome",
			" (VG) Liquid Metal", " (VG) Skynet", "(CW) Desedance", "(VG) Greenthumb" };
		static const char* current_item = " Select Camo";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cCamoList); n++)
			{
				bool is_selected = (current_item == cCamoList[n]);
				if (ImGui::Selectable(cCamoList[n], is_selected))
					current_item = cCamoList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						JaysModz->msettings.iCamoSelection = 111;
					}
					if (n == 1)
					{
						JaysModz->msettings.iCamoSelection = 112;
					}
					if (n == 2)
					{
						JaysModz->msettings.iCamoSelection = 113;
					}
					if (n == 3)
					{
						JaysModz->msettings.iCamoSelection = 114;
					}
					if (n == 4)
					{
						JaysModz->msettings.iCamoSelection = 133;
					}
					if (n == 5)
					{
						JaysModz->msettings.iCamoSelection = 134;
					}
					if (n == 6)
					{
						JaysModz->msettings.iCamoSelection = 135;
					}
					if (n == 7)
					{
						JaysModz->msettings.iCamoSelection = 242;
					}
					if (n == 8)
					{
						JaysModz->msettings.iCamoSelection = 243;
					}
					if (n == 9)
					{
						JaysModz->msettings.iCamoSelection = 244;
					}
					if (n == 10)
					{
						JaysModz->msettings.iCamoSelection = 345;
					}
					if (n == 11)
					{
						JaysModz->msettings.iCamoSelection = 346;
					}
					if (n == 12)
					{
						JaysModz->msettings.iCamoSelection = 350;
					}
					if (n == 13)
					{
						JaysModz->msettings.iCamoSelection = 349;
					}
					if (n == 14)
					{
						JaysModz->msettings.iCamoSelection = 402;
					}
					if (n == 15)
					{
						JaysModz->msettings.iCamoSelection = 403;
					}
					if (n == 16)
					{
						JaysModz->msettings.iCamoSelection = 404;
					}
					if (n == 17)
					{
						JaysModz->msettings.iCamoSelection = 160;
					}
					if (n == 18)
					{
						JaysModz->msettings.iCamoSelection = 2;
					}
					if (n == 19)
					{
						JaysModz->msettings.iCamoSelection = 3;
					}
					if (n == 20)
					{
						JaysModz->msettings.iCamoSelection = 509;
					}
					if (n == 21)
					{
						JaysModz->msettings.iCamoSelection = 510;
					}
					if (n == 22)
					{
						JaysModz->msettings.iCamoSelection = 511;
					}
					if (n == 23)
					{
						JaysModz->msettings.iCamoSelection = 512;
					}
					if (n == 24)
					{
						JaysModz->msettings.iCamoSelection = 513;
					}
					if (n == 25)
					{
						JaysModz->msettings.iCamoSelection = 222;
					}
					if (n == 26)
					{
						JaysModz->msettings.iCamoSelection = 319;
					}

				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxClanTagSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cClanTagSelectorList[] = { " Logo KING", " Logo BLIZZARD", " Logo IW", " Logo RVN", " Logo SHG"," Logo DW"," Logo HMS"," Logo BNOX"," Logo 3ARC"," Logo VV"," Logo TFB"," Red 1W"," Red LW"," Red IW DEV"," Red RAVN"," Red RAVEN"," Red R4VEN", " Red OW", " Red BN0X"," Red 34RC"," Red ATVI", " Red MLG" };
		static const char* current_item = " Select Clan Tag";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cClanTagSelectorList); n++)
			{
				bool is_selected = (current_item == cClanTagSelectorList[n]);
				if (ImGui::Selectable(cClanTagSelectorList[n], is_selected))
					current_item = cClanTagSelectorList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						JaysModz->msettings.sPresetClanTag = "KING";
					}
					if (n == 1)
					{
						JaysModz->msettings.sPresetClanTag = "BLIZ";
					}
					if (n == 2)
					{
						JaysModz->msettings.sPresetClanTag = "iw";
					}
					if (n == 3)
					{
						JaysModz->msettings.sPresetClanTag = "rvn";
					}
					if (n == 4)
					{
						JaysModz->msettings.sPresetClanTag = "shg";
					}
					if (n == 5)
					{
						JaysModz->msettings.sPresetClanTag = "dw";
					}
					if (n == 6)
					{
						JaysModz->msettings.sPresetClanTag = "hms";
					}
					if (n == 7)
					{
						JaysModz->msettings.sPresetClanTag = "bnox";
					}
					if (n == 8)
					{
						JaysModz->msettings.sPresetClanTag = "3arc";
					}
					if (n == 9)
					{
						JaysModz->msettings.sPresetClanTag = "vv";
					}
					if (n == 10)
					{
						JaysModz->msettings.sPresetClanTag = "tfb";
					}
					if (n == 11)
					{
						JaysModz->msettings.sPresetClanTag = "1W";
					}
					if (n == 12)
					{
						JaysModz->msettings.sPresetClanTag = "LW";
					}
					if (n == 13)
					{
						JaysModz->msettings.sPresetClanTag = "IWDev";
					}
					if (n == 14)
					{
						JaysModz->msettings.sPresetClanTag = "RAVN";
					}
					if (n == 15)
					{
						JaysModz->msettings.sPresetClanTag = "RAVEN";
					}
					if (n == 16)
					{
						JaysModz->msettings.sPresetClanTag = "R4VEN";
					}
					if (n == 17)
					{
						JaysModz->msettings.sPresetClanTag = "OW";
					}
					if (n == 18)
					{
						JaysModz->msettings.sPresetClanTag = "BN0X";
					}
					if (n == 19)
					{
						JaysModz->msettings.sPresetClanTag = "34RC";
					}
					if (n == 20)
					{
						JaysModz->msettings.sPresetClanTag = "ATVI";
					}
					if (n == 21)
					{
						JaysModz->msettings.sPresetClanTag = "MLG";
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxOpSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cOpSelectorList[] =
		{
		 "Lava Man",
		 "Egyptian Man" ,
		 "Witch Bitch",
		 "Ghost Samuri",
		 "Power Ranger",
		 "Panda",
		 "Red Flashy",
		 "Scarecrow Gas",
		 "Crystalized DMU",
		 "Desiple",
		 "Maxis Bride",
		 "Rabbit",
		 "Ghost Face",
		 "Race Guy",
		 "Checker",
		 "Aurora Borealis",
		 "Big fire samuri",
		 "Godzilla",
		 "Mecha Godzilla",
		 "T-1000 terminator",
		 "Gold terminator",
		 "Silver terminator" ,
		 "Normal terminator" ,
		 "Egyption god" ,
		 "Gold snoop",
		 "Alien",
		 "White Mirage",
		 "Hydrodynamic",
		 "Ember",
		 "Clown",
		 "Honshu Guardian",
		 "Doom Slayer",
		 "Nephilim",
		 "Hazel",
		 "Dark Resistance",
		 "Cha-Cha",
		 "Concealed Weapon",
		 "Tigris Templar",
		 "Night Terror",
		 "Famine",
		 "War",
		 "Astrakhan",
		 "Pink Hippie",
		 "Hangman",
		 "Laboratory",
		 "Havoc",
		 "Mythical Decay",
		 "Lumens",
		 "Noir",
		 "Double Agent",
		 "Town Runner",
		 "War Lock",
		 "GoldLeaf",
		 "Samurai",
		 "Kyubi",
		 "Yokai Master",
		 "Investigator",
		 "Battle Oni",
		 "Easter Bunny",
		 "Fitness Instructor",
		 "Funny Bone",
		 "OutLaw",
		 "Paladin",
		 "Rambo",
		 "Silver Mendez",
		 "CDL CW",
		 "Testing Dummy",
		 "Pestilence",
		 "Ninja Girl",
		 "TypeFace",
		 "Blue Cartel",
		 "Gold Cartel",
		 "Tom Brady",
		 "White Ninja",
		 "Robot Cat",
		 "Fox Iskra",
		 "VG CDL Gold",
		 "Monkey Man",
		 "Redriding Hood",
		 "Masked Cloak",
		 "Armored Titan",

		};
		static const char* current_item = " Select Operator";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cOpSelectorList); n++)
			{
				bool is_selected = (current_item == cOpSelectorList[n]);
				if (ImGui::Selectable(cOpSelectorList[n], is_selected))
					current_item = cOpSelectorList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						JaysModz->msettings.iOPSelection = 1557;
					}
					if (n == 1)
					{
						JaysModz->msettings.iOPSelection = 1558;
					}
					if (n == 2)
					{
						JaysModz->msettings.iOPSelection = 1570;
					}
					if (n == 3)
					{
						JaysModz->msettings.iOPSelection = 1562;
					}
					if (n == 4)
					{
						JaysModz->msettings.iOPSelection = 1550;
					}
					if (n == 5)
					{
						JaysModz->msettings.iOPSelection = 1563;
					}
					if (n == 6)
					{
						JaysModz->msettings.iOPSelection = 1544;
					}
					if (n == 7)
					{
						JaysModz->msettings.iOPSelection = 1541;
					}
					if (n == 8)
					{
						JaysModz->msettings.iOPSelection = 1530;
					}
					if (n == 9)
					{
						JaysModz->msettings.iOPSelection = 1629;
					}
					if (n == 10)
					{
						JaysModz->msettings.iOPSelection = 1363;
					}
					if (n == 11)
					{
						JaysModz->msettings.iOPSelection = 1638;
					}
					if (n == 12)
					{
						JaysModz->msettings.iOPSelection = 1580;
					}
					if (n == 13)
					{
						JaysModz->msettings.iOPSelection = 1108;
					}
					if (n == 14)
					{
						JaysModz->msettings.iOPSelection = 1599;
					}
					if (n == 15)
					{
						JaysModz->msettings.iOPSelection = 1595;
					}
					if (n == 16)
					{
						JaysModz->msettings.iOPSelection = 2861;
					}
					if (n == 17)
					{
						JaysModz->msettings.iOPSelection = 2840;
					}
					if (n == 18)
					{
						JaysModz->msettings.iOPSelection = 2839;
					}
					if (n == 19)
					{
						JaysModz->msettings.iOPSelection = 2929;
					}
					if (n == 20)
					{
						JaysModz->msettings.iOPSelection = 2919;
					}
					if (n == 21)
					{
						JaysModz->msettings.iOPSelection = 2918;
					}
					if (n == 22)
					{
						JaysModz->msettings.iOPSelection = 2916;
					}
					if (n == 23)
					{
						JaysModz->msettings.iOPSelection = 2794;
					}
					if (n == 24)
					{
						JaysModz->msettings.iOPSelection = 2791;
					}
					if (n == 25)
					{
						JaysModz->msettings.iOPSelection = 2904;
					}
					if (n == 26)
					{
						JaysModz->msettings.iOPSelection = 2078;
					}
					if (n == 27)
					{
						JaysModz->msettings.iOPSelection = 2938;
					}
					if (n == 28)
					{
						JaysModz->msettings.iOPSelection = 1504;
					}
					if (n == 29)
					{
						JaysModz->msettings.iOPSelection = 1045;
					}
					if (n == 30)
					{
						JaysModz->msettings.iOPSelection = 1699;
					}
					if (n == 31)
					{
						JaysModz->msettings.iOPSelection = 2925;
					}
					if (n == 32)
					{
						JaysModz->msettings.iOPSelection = 2954;
					}
					if (n == 33)
					{
						JaysModz->msettings.iOPSelection = 2964;
					}
					if (n == 34)
					{
						JaysModz->msettings.iOPSelection = 2846;
					}
					if (n == 35)
					{
						JaysModz->msettings.iOPSelection = 2963;
					}
					if (n == 36)
					{
						JaysModz->msettings.iOPSelection = 1726;
					}
					if (n == 37)
					{
						JaysModz->msettings.iOPSelection = 2984;
					}
					if (n == 38)
					{
						JaysModz->msettings.iOPSelection = 2905;
					}
					if (n == 39)
					{
						JaysModz->msettings.iOPSelection = 2882;
					}
					if (n == 40)
					{
						JaysModz->msettings.iOPSelection = 2861;
					}
					if (n == 41)
					{
						JaysModz->msettings.iOPSelection = 2077;
					}
					if (n == 42)
					{
						JaysModz->msettings.iOPSelection = 2981;
					}
					if (n == 43)
					{
						JaysModz->msettings.iOPSelection = 2915;
					}
					if (n == 44)
					{
						JaysModz->msettings.iOPSelection = 1569;
					}
					if (n == 45)
					{
						JaysModz->msettings.iOPSelection = 1390;
					}
					if (n == 46)
					{
						JaysModz->msettings.iOPSelection = 2902;
					}
					if (n == 47)
					{
						JaysModz->msettings.iOPSelection = 1560;
					}
					if (n == 48)
					{
						JaysModz->msettings.iOPSelection = 1503;
					}
					if (n == 49)
					{
						JaysModz->msettings.iOPSelection = 1094;
					}
					if (n == 50)
					{
						JaysModz->msettings.iOPSelection = 2883;
					}
					if (n == 51)
					{
						JaysModz->msettings.iOPSelection = 1501;
					}
					if (n == 52)
					{
						JaysModz->msettings.iOPSelection = 1502;
					}
					if (n == 53)
					{
						JaysModz->msettings.iOPSelection = 1500;
					}
					if (n == 54)
					{
						JaysModz->msettings.iOPSelection = 1499;
					}
					if (n == 55)
					{
						JaysModz->msettings.iOPSelection = 2799;
					}
					if (n == 56)
					{
						JaysModz->msettings.iOPSelection = 1473;
					}
					if (n == 57)
					{
						JaysModz->msettings.iOPSelection = 1639;
					}
					if (n == 58)
					{
						JaysModz->msettings.iOPSelection = 1297;
					}
					if (n == 59)
					{
						JaysModz->msettings.iOPSelection = 1380;
					}
					if (n == 60)
					{
						JaysModz->msettings.iOPSelection = 1359;
					}
					if (n == 61)
					{
						JaysModz->msettings.iOPSelection = 1464;
					}
					if (n == 62)
					{
						JaysModz->msettings.iOPSelection = 1640;
					}
					if (n == 63)
					{
						JaysModz->msettings.iOPSelection = 1371;
					}
					if (n == 64)
					{
						JaysModz->msettings.iOPSelection = 2973;
					}
					if (n == 65)
					{
						JaysModz->msettings.iOPSelection = 1234;
					}
					if (n == 66)
					{
						JaysModz->msettings.iOPSelection = 1323;
					}

					if (n == 67)
					{
						JaysModz->msettings.iOPSelection = 2999;
					}


					if (n == 68)
					{
						JaysModz->msettings.iOPSelection = 1674;
					}


					if (n == 69)
					{
						JaysModz->msettings.iOPSelection = 2897;
					}


					if (n == 70)
					{
						JaysModz->msettings.iOPSelection = 2970;
					}


					if (n == 71)
					{
						JaysModz->msettings.iOPSelection = 2972;
					}

					if (n == 72)
					{
						JaysModz->msettings.iOPSelection = 2879;
					}

					if (n == 73)
					{
						JaysModz->msettings.iOPSelection = 2921;
					}

					if (n == 74)
					{
						JaysModz->msettings.iOPSelection = 2927;
					}

					if (n == 75)
					{
						JaysModz->msettings.iOPSelection = 2888;
					}
					if (n == 76)
					{
						JaysModz->msettings.iOPSelection = 2845;
					}
					if (n == 77)
					{
						JaysModz->msettings.iOPSelection = 2838;
					}
					if (n == 78)
					{
						JaysModz->msettings.iOPSelection = 2793;
					}

					if (n == 79)
					{
						JaysModz->msettings.iOPSelection = 1758;
					}

					if (n == 80)
					{
						JaysModz->msettings.iOPSelection = 1803;
					}

				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ComboBoxStatSelector(const char* featureName, int size, BOOL newLine)
	{
		const char* cCamoList[] = { " Rebirth",  " Battle Royale" };
		static const char* current_item = " Select Gamemode";
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, current_item))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cCamoList); n++)
			{
				bool is_selected = (current_item == cCamoList[n]);
				if (ImGui::Selectable(cCamoList[n], is_selected))
					current_item = cCamoList[n];
				if (ImGui::IsItemClicked(is_selected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						if (JaysModz->msettings.bMiscBRSelected)
						{
							JaysModz->msettings.bMiscBRSelected = false;
						}
						JaysModz->msettings.bMiscRebirthSelected = true;
					}
					if (n == 1)
					{
						if (JaysModz->msettings.bMiscRebirthSelected)
						{
							JaysModz->msettings.bMiscRebirthSelected = false;
						}
						JaysModz->msettings.bMiscBRSelected = true;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void InputLoadoutName(const char* featureName, int size, BOOL newLine)
	{
		ImGui::PushItemWidth(size);
		ImGui::InputText(featureName, cLoadoutEditorBuf, IM_ARRAYSIZE(cLoadoutEditorBuf));
		ImGui::PopItemWidth();

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void InputCustomClanTag(const char* featureName, int size, BOOL newLine)
	{
		ImGui::PushItemWidth(size);
		ImGui::InputText(featureName, cCustomClanTagBuf, IM_ARRAYSIZE(cCustomClanTagBuf));
		ImGui::PopItemWidth();

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonPageMultiple(const char* page1Name, const char* page2Name, bool* featureBool, ImVec2 pos, ImVec2 size)
	{
		ImGui::SetCursorPos(pos);
		if (!*featureBool)
		{
			if (ImGui::Button(page2Name, size))
			{
				*featureBool = !*featureBool;
			}
		}
		else
		{
			if (ImGui::Button(page1Name, size))
			{
				*featureBool = !*featureBool;
			}
		}
	}

	void ButtonPageSingle(const char* pageName, bool* featureBool, ImVec2 pos, ImVec2 size)
	{
		ImGui::SetCursorPos(pos);
		if (ImGui::Button(pageName, size))
		{
			*featureBool = !*featureBool;
		}
	}

	void ButtonIcon(const char* buttonName, bool* featureBool, ImVec2 buttonPos, ImVec2 size, ImColor textColor)
	{
		ImGui::SCP(buttonPos.x, buttonPos.y);
		ImGui::PushFont(FA);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(38, 38, 38, 255)));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(32, 32, 32, 255)));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(34, 34, 34, 255)));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(64, 64, 64, 255)));
		if (ImGui::Button(buttonName, size))
		{
			*featureBool = !*featureBool;
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SCP(buttonPos.x, buttonPos.y);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(textColor)));
			if (ImGui::Button(buttonName, size))
			{
				*featureBool = !*featureBool;
			}
			ImGui::PopStyleColor();
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(4);
	}

	void ButtonIcon2(const char* buttonName, int* page, int pageNumber, ImVec2 buttonPos, ImVec2 size)
	{
		ImGui::SCP(buttonPos.x, buttonPos.y);
		ImGui::PushFont(FA);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(38, 38, 38, 255)));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(32, 32, 32, 255)));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(34, 34, 34, 255)));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(64, 64, 64, 255)));
		ImGui::PushStyleColor(ImGuiCol_Text, iTab == pageNumber ? active : inactive);
		if (ImGui::Button(buttonName, size))
		{
			*page = pageNumber;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(5);
	}

	void ButtonIndicator(ImVec2 buttonPos)
	{
		if (iTab == 0)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::SameLine();
			ImGui::SCP(buttonPos.x - 22, buttonPos.y + 12);
			ImGui::Button("", ImVec2(5, 25));
			ImGui::PopStyleColor(4);
		}
		if (iTab == 1)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::SameLine();
			ImGui::SCP(buttonPos.x - 22, buttonPos.y + 12);
			ImGui::Button("", ImVec2(5, 25));
			ImGui::PopStyleColor(4);
		}
		if (iTab == 2)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::SameLine();
			ImGui::SCP(buttonPos.x - 22, buttonPos.y + 12);
			ImGui::Button("", ImVec2(5, 25));
			ImGui::PopStyleColor(4);
		}
		if (iTab == 3)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(0, 68, 170, 255)));
			ImGui::SameLine();
			ImGui::SCP(buttonPos.x - 22, buttonPos.y + 12);
			ImGui::Button("", ImVec2(5, 25));
			ImGui::PopStyleColor(4);
		}
	}

	void KnobSliderSCP(const char* featureName, int* featureInt, int min, int max, ImVec2 pos, BOOL sameLine, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGuiKnobs::KnobInt(featureName, featureInt, min, max, 10136, NULL, ImGuiKnobVariant_WiperDot);

		if (sameLine)
		{
			ImGui::SameLine();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void KnobFloatSliderSCP(const char* featureName, float* featureInt, float min, float max, ImVec2 pos, BOOL sameLine, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::PushFont(Body2);
		ImGuiKnobs::Knob(featureName, featureInt, min, max, 1, NULL, ImGuiKnobVariant_WiperDot);
		ImGui::PopFont();

		if (sameLine)
		{
			ImGui::SameLine();
		}

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ColorEditNL(const char* featureName, float color[3], BOOL newLine)
	{
		ImGui::ColorEdit3(featureName, color, ImGuiColorEditFlags_NoInputs);

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine)
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = ImGui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;

		ImGui::InvisibleButton(toggleName, ImVec2(width, height));
		if (ImGui::IsItemClicked())
			*featureBool = !*featureBool;

		float t = *featureBool ? 1.0f : 0.0f;

		ImGuiContext& g = *GImGui;
		float ANIM_SPEED = 0.08f;
		if (g.LastActiveId == g.CurrentWindow->GetID(toggleName))// && g.LastActiveIdTimer < ANIM_SPEED)
		{
			float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
			t = *featureBool ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 0.40f), ImVec4(ImColor(0, 68, 170, 200)), t)); // ImColor(255, 0, 255, 255) // 0.64f, 0.83f, 0.34f, 1.0f
		else
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 0.60f), ImVec4(ImColor(0, 68, 170, 255)), t)); // ImColor(255, 0, 255, 255) // 0.56f, 0.83f, 0.26f, 1.0f

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		ImGui::SameLine();
		ImGui::Text(toggleName);

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void DrawLine(int x, int y, int x_pos, int y_pos, ImColor color)
	{
		ImDrawList* Draw = ImGui::GetWindowDrawList();

		ImGui::SCP(x, y);

		ImVec2 p = ImGui::GetCursorScreenPos();

		ImGui::SCP(x_pos, y_pos);

		ImVec2 p2 = ImGui::GetCursorScreenPos();

		Draw->AddLine(ImVec2(p.x, p.y), ImVec2(p2.x, p2.y), ImColor(color), 2.0f);
	}

	float GetX()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float GetY()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	void UITheme()
	{

		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowBorderSize = 4;
		Style->FrameBorderSize = 0;
		Style->WindowRounding = 10;
		Style->ChildRounding = 12;
		Style->ChildBorderSize = 2;
		Style->FrameRounding = 6;
		Style->FrameBorderSize = 2;
		Style->ScrollbarSize = 0;
		Style->WindowPadding = ImVec2(0, 0);
		Style->FramePadding = ImVec2(0, 0);
		Style->ItemSpacing = ImVec2(0, 0);
		Style->ItemInnerSpacing = ImVec2(0, 0);
		Style->IndentSpacing = 0;
		Style->DisplayWindowPadding = ImVec2(0, 0);
		Style->Colors[ImGuiCol_WindowBg] = ImColor(1, 1, 1, 255);
		Style->Colors[ImGuiCol_Border] = ImColor(141, 141, 141, 255); // ImColor(43, 22, 43, 255); // ImColor(255, 255, 255, 155);
		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_SliderGrab] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_Button] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 68, 170, 200);
		Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 68, 170, 155);
		Style->Colors[ImGuiCol_Separator] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_SeparatorActive] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 255, 255);
		Style->Colors[ImGuiCol_HeaderHovered] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_Header] = ImColor(0, 68, 170, 255);
		Style->Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 0, 255, 255);
	}

	void MainUISetup()
	{
		windowFlagsChild |= windowFlagsChild | ImGuiWindowFlags_NoScrollWithMouse;

		// Main Child Window to Store All other Childs in.
		if (ImGui::BeginChild("MainChildWindow", ImVec2(825, 549), true, windowFlagsChild)) // Main Size of the Entire UI. this line is the entire menu window. yes
		{
			// Left Side Task Bar.
			ImGui::SCP(0, 0);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(1, 1, 1, 255)));
			if (ImGui::BeginChild("TopLogo", ImVec2(155, 50), false, windowFlagsChild))
			{
				ImGui::SCPY(12);
				//ImGui::PushFont(Header);
				//ImGui::CenterText("JaysModz", 0, FALSE, FALSE);
			//	ImGui::CenterText("VIP-AIO", 0, FALSE, FALSE);
			//	ImGui::PopFont();
				//ImGui::HoroizontalLine(100, 50, 1, 25, 100);
				// Page Buttons.
				ImGui::ButtonIcon2("1", &iTab, 0, ImVec2(12, 10), ImVec2(37, 34)); // Exploits Page.
				ImGui::ButtonIcon2("2", &iTab, 1, ImVec2(57, 10), ImVec2(37, 34)); // Misc. Page.
				//ImGui::ButtonIcon2("3", &iTab, 2, ImVec2(102, 10), ImVec2(37, 34));
			//	ImGui::ButtonIcon2("3", &iTab, 3, ImVec2(145, 12), ImVec2(37, 34));
				if (iTab == 0)
				{
					ImGui::ButtonIndicator(ImVec2(12, 10));
				}
				if (iTab == 1)
				{
					ImGui::ButtonIndicator(ImVec2(57, 10));
				}
				if (iTab == 2)
				{
					ImGui::ButtonIndicator(ImVec2(104, 10));
				}
				if (iTab == 3)
				{
				//	ImGui::ButtonIndicator(ImVec2(24, 435));
				}
				ImGui::CenterTextSCP("", 550);
			} ImGui::EndChild();
			ImGui::PopStyleColor();

			// Vertical Line to Separate left side task bar.
			//ImGui::VerticalLine(100, 1, 100, 0);

			// Exploit Window.
			if (iTab == 0) //start of tab 1 but in index, it's as 0.. Basically, 0 = 1. No, you put in none lol you put it here
			{
				// Loadout Name Editor Window.
				ImGui::SCP(8, 90);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
				if (ImGui::BeginChild("LoadoutNameChangerWindow", ImVec2(260, 211), false, windowFlagsChild))
				{
					ImGui::SCPY(10);
					ImGui::CenterText("Loadout Name Changer", 10, FALSE, TRUE);
					ImGui::HoroizontalLineNL(300, 240, 1, 10, TRUE);
					ImGui::Indent(22);
					ImGui::ComboBoxLoadoutNameSelector(("##LoadoutSelectorCombo"), 215, TRUE);
					ImGui::InputLoadoutName(("##LoadoutNameEditor"), 215, TRUE);
					ImGui::Unindent(22);
					ImGui::ButtonSCP("Set", &JaysModz->msettings.bSetClassName, ImVec2(102, 135), ImVec2(65, 20), TRUE);
					ImGui::ButtonSCP("Set All", &JaysModz->msettings.bSetClassNameAll, ImVec2(172, 135), ImVec2(65, 20), TRUE);
					ImGui::ButtonSwitchSCP("MP / WZ", &JaysModz->msettings.bMiscMPWZClassName, ImVec2(22, 135), ImVec2(75, 20), TRUE);
					if (!JaysModz->msettings.bMiscMPWZClassName)
					{
						ImGui::SCPY(180);
						ImGui::CenterText("- Editing MP Loadout -", 20, FALSE, FALSE);
					}
					else
					{
						ImGui::SCPY(180);
						ImGui::CenterText("- Editing WZ Loadout -", 20, FALSE, FALSE);
					}
				} ImGui::EndChild();
				ImGui::PopStyleColor();

				// Double Gun Editor Window.
				ImGui::SCP(8, 313);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
				if (ImGui::BeginChild("DoubleGunEditorWindow", ImVec2(260, 226), false, windowFlagsChild))
				{
					ImGui::SCPY(10);
					ImGui::CenterText("Double Gun Editor", 10, FALSE, TRUE);
					ImGui::HoroizontalLineNL(400, 240, 1, 10, TRUE);
					ImGui::CenterText("Must Have Overkill Equipped", 0, FALSE, TRUE);
					ImGui::Indent(22);
					ImGui::ComboBoxDGLoadoutSelector("##DoubleGunsSelectorCombo", 215, TRUE);
					ImGui::Unindent(22);
					ImGui::ButtonSCP("Set", &JaysModz->msettings.bSetDoubleGun, ImVec2(102, 135), ImVec2(65, 20), TRUE);
					ImGui::ButtonSCP("Set All", &JaysModz->msettings.bSetDoubleGunAll, ImVec2(172, 135), ImVec2(65, 20), TRUE);
					ImGui::ButtonSwitchSCP("MP / WZ", &JaysModz->msettings.bMiscMPWZDG, ImVec2(22, 135), ImVec2(75, 20), TRUE);
					if (!JaysModz->msettings.bMiscMPWZDG)
					{
						ImGui::SCPY(180);
						ImGui::CenterText("- Editing MP Double Gun -", 30, FALSE, FALSE);
					}
					else
					{
						ImGui::SCPY(180);
						ImGui::CenterText("- Editing WZ Double Gun -", 30, FALSE, FALSE);
					}
				} ImGui::EndChild();
				ImGui::PopStyleColor();

				ImGui::VerticalLineCustom(700, 300, 400, 150);

				// ClanTag Editor Window.
				ImGui::SCP(276, 90);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
				if (ImGui::BeginChild("ClanTagEditorWindow", ImVec2(260, 211), false, windowFlagsChild))
				{
					ImGui::SCPY(10);
					ImGui::CenterText("Clan Tag Editor", 10, FALSE, TRUE);
					ImGui::HoroizontalLineNL(500, 240, 1, 10, TRUE);
					ImGui::Indent(22);
					ImGui::ComboBoxClanTagSelector("##ClanTagSelectorCombo", 215, TRUE);
					ImGui::Unindent(22);
					ImGui::ButtonSCP("Set Clan Tag", &JaysModz->msettings.bSetPresetClanTag, ImVec2(22, 103), ImVec2(215, 20), TRUE);
					ImGui::Indent(22);
					ImGui::InputCustomClanTag("##CustomClanTagInput", 215, TRUE);
					ImGui::Unindent(22);
					ImGui::ButtonSCP("Set Custom Tag", &JaysModz->msettings.bSetCustomClanTag, ImVec2(22, 176), ImVec2(215, 20), FALSE);
				} ImGui::EndChild();
				ImGui::PopStyleColor();

				// CAMO EDITOR
				ImGui::SCP(276, 313);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
				if (ImGui::BeginChild("CamoEditerWindow", ImVec2(260, 226), false, windowFlagsChild))
				{
					ImGui::SCPY(10);
					ImGui::CenterText("Camo Swap Editor", 10, FALSE, TRUE);
					ImGui::HoroizontalLineNL(900, 240, 1, 10, TRUE);
					ImGui::Indent(22);
					ImGui::ComboBoxCamoLoadoutSelector("##CamoEditorSelectorCombo", 215, TRUE);
					ImGui::ComboBoxWeaponSelector("##CamoEditorWeaponSelectorCombo", 215, TRUE);
					ImGui::ComboBoxCamoSelector("##CamoEditorCombo", 215, TRUE);
					ImGui::Unindent(22);
					ImGui::ButtonSCP("Set", &JaysModz->msettings.bSetCamo, ImVec2(102, 172), ImVec2(65, 20), TRUE);
					ImGui::ButtonSCP("Set All", &JaysModz->msettings.bSetCamoAll, ImVec2(172, 172), ImVec2(65, 20), TRUE);
					ImGui::ButtonSwitchSCP("MP / WZ", &JaysModz->msettings.bMiscMPWZCamoClass, ImVec2(22, 172), ImVec2(75, 20), TRUE);
					if (!JaysModz->msettings.bMiscMPWZCamoClass)
					{
						ImGui::SCPY(210);
						ImGui::CenterText("- Editing MP Loadout -", 40, FALSE, FALSE);
					}
					else
					{
						ImGui::SCPY(210);
						ImGui::CenterText("- Editing WZ Loadout -", 40, FALSE, FALSE);

					} ImGui::EndChild();
					ImGui::PopStyleColor();

					ImGui::SCP(545, 90);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
					if (ImGui::BeginChild("OperatorEditerWindow", ImVec2(260, 211), false, windowFlagsChild))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Operator Swap Editor", 10, FALSE, TRUE);
						ImGui::HoroizontalLineNL(1000, 240, 1, 10, TRUE);
						ImGui::Indent(22);
						ImGui::ComboBoxOpSelector("##ClassSelectorCombo", 215, TRUE);
						ImGui::Unindent(22);
						ImGui::ButtonSwitchSCP("MP / WZ", &JaysModz->msettings.bMiscMPWZOS, ImVec2(22, 103), ImVec2(215, 20), TRUE);
						if (!JaysModz->msettings.bMiscMPWZOS)
						{
							ImGui::ButtonSL("Set Team 1", &JaysModz->msettings.bSetOPMP1, 22, ImVec2(105, 20), TRUE, FALSE);
							ImGui::ButtonSL("Set Team 2", &JaysModz->msettings.bSetOPMP2, 132, ImVec2(105, 20), FALSE, FALSE);
							ImGui::SCPY(210);
							ImGui::CenterText("- Editing MP Operators -", 50, FALSE, FALSE);
						}
						else
						{
							ImGui::ButtonNL("Set OP", &JaysModz->msettings.bSetOPWZ, 22, ImVec2(215, 20), FALSE);
							ImGui::SCPY(210);
							ImGui::CenterText("- Editing WZ Operators -", 50, FALSE, FALSE);
							ImGui::Unindent(22);
						}
						ImGui::EndChild();
						ImGui::PopStyleColor();
						ImGui::SCP(545, 313);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
						if (ImGui::BeginChild("MiscFeatureWindow+", ImVec2(260, 226), true, windowFlagsChild))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Game Exploits", 10, FALSE, TRUE);
							ImGui::HoroizontalLineNL(800, 240, 1, 10, TRUE);
							ImGui::Indent(22);
							ImGui::ToggleNL("  No Owner Check", &JaysModz->msettings.b_owner, TRUE);
							ImGui::SliderIntNL("  Map", &JaysModz->msettings.iMiniMapValue, &JaysModz->msettings.b_map, 1, 10, 100, FALSE, TRUE);
							ImGui::SliderIntNL("  FOV", &JaysModz->msettings.iFovValue, &JaysModz->msettings.b_fov, 1, 10, 100, FALSE, FALSE);
						}
						ImGui::Unindent(22);
						ImGui::EndChild();
						ImGui::PopStyleColor();
					
				
					}
				}
            } //this bracket ends tab 1, got time

		//you put it outside into the Main menu window, hence why it appeared on all tabs. You didn't put into the tab 0.. Nope, let me show you an easy tip

			// Misc Window.
			if (iTab == 1)
			{
				static const char* gametype[] = { "Multiplayer", "Warzone" };
				static const char* current_type = "Warzone";
				ImGui::SCP(8, 65);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
				if (ImGui::BeginCombo("##GAMETYPE", current_type)) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < IM_ARRAYSIZE(gametype); n++)
					{
						bool is_selected = (current_type == gametype[n]); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(gametype[n], is_selected))
							current_type = gametype[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
					ImGui::EndCombo();
				}
				ImGui::Dummy(ImVec2(0.0f, 1.0f));

				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}
				ImGui::InputTextWithHint(xorstr_("##TestWeapon"), xorstr_("Operator skin Id (1-2925)"), operator_skin, ARRAYSIZE(operator_skin));
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				if (ImGui::Button(xorstr_("Set Operator"), ImVec2(-5, 32)))
				{
					if (current_type == "Multiplayer")
					{
						JaysModz->msettings.iGameMode = 0;
						setOperators("default_western", atoi(operator_skin));
					}
					if (current_type == "Warzone")
					{
						JaysModz->msettings.iGameMode = 1;
						setOperators("default_western", atoi(operator_skin));
					}
				}

			} ImGui::Unindent(22);
			ImGui::EndChild();
			ImGui::PopStyleColor();
		}	ImGui::EndGroupBox();
    
					

		



		// Cosmetics Window.
		if (iTab == 2)
		{
			ImGui::SCP(110, 10);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(141, 141, 141, 255)));
			if (ImGui::BeginChild("MiscFeatureWindow", ImVec2(260, 580), false, windowFlagsChild)) // 580
			{
			//	ImGui::SCPY(10);
			//	ImGui::CenterText("ESP OUTLINES", 10, FALSE, TRUE);
			//	ImGui::HoroizontalLineNL(600, 240, 1, 10, TRUE);
			//	ImGui::Indent(22);
			//	ImGui::ToggleNL("  Enable Esp", &JaysModz->msettings.chams, TRUE);
				//ImGui::Spacing();
				//ImGui::ToggleNL("  Only Visible", &JaysModz->msettings.visibleOutlines, TRUE);
				//ImGui::Spacing();
				//ImGui::ToggleNL("  Only Invisible", &JaysModz->msettings.notVisibleOutlines, TRUE);
				//ImGui::Spacing();
				//ImGui::ToggleNL("  Fill Outlines", &JaysModz->msettings.chamFill, TRUE);
				//ImGui::Spacing();
				//ImGui::ToggleNL("  Loot", &JaysModz->msettings.lootChams, TRUE);
				//ImGui::SCPY(10);
				//ImGui::CenterText("ESP SETTINGS", 10, FALSE, TRUE);
				//ImGui::HoroizontalLineNL(800, 240, 1, 10, TRUE);
				//ImGui::Indent(22);
				//ImGui::ToggleNL("  RGB Mode", &JaysModz->msettings.rgbChams, TRUE);
				//ImGui::Spacing();
				///ImGui::ColorEdit3("  Loot Color", (float*)&item_colorVec44, TRUE);
				//ImGui::Spacing();
				//ImGui::ColorEdit3("  Player Color", (float*)&player_colorVec44, TRUE);

				//JaysModz->msettings.playerColor = ImGui::ColorConvertFloat4ToU32(player_colorVec44);
				//JaysModz->msettings.lootColor = ImGui::ColorConvertFloat4ToU32(item_colorVec44);
				ImGui::Spacing();
				ImGui::Unindent(22);
				ImGui::EndChild();
				ImGui::PopStyleColor();
			}

		}
			
			// Stats Window.
			if (iTab == 3)
			{
				// Misc Window.
				ImGui::SCP(110, 10);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(26, 26, 26, 255)));
				if (ImGui::BeginChild("StatEditorWindow", ImVec2(580, 580), true, windowFlagsChild))
				{
					ImGui::SCPY(10);
					ImGui::CenterText("Stat Editor", 10, FALSE, TRUE);
					ImGui::HoroizontalLineNL(1100, 560, 1, 10, TRUE);
					ImGui::SCPX(200);
					ImGui::ComboBoxStatSelector("##StatSelector", 180, TRUE);
					if (JaysModz->msettings.bMiscRebirthSelected)
					{
						ImGui::PushFont(Body2);
						ImGui::CenterText("- Click and Hold on the Circle Slider and Move UP/DOWN to Change Value -", 100, FALSE, FALSE);
						ImGui::KnobSliderSCP("RB Wins", &JaysModz->msettings.iRebirthWins, 1, 9999999, ImVec2(137, 180), TRUE, FALSE);
       					if (ImGui::Button(xorstr_("Set RB Wins", ImVec2(107, 290), ImVec2(125, 18), TRUE)))
	                     
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"wins");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iRebirthWins);
						}
						//
						ImGui::KnobSliderSCP("RB Top 5", &JaysModz->msettings.iRebirthTop5, 1, 9999999, ImVec2(367, 180), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set RB Top 5", ImVec2(337, 290), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"topFive");
							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iRebirthTop5);

						}
						//
						ImGui::KnobSliderSCP("RB Kills", &JaysModz->msettings.iRebirthKills, 1, 9999999, ImVec2(137, 330), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set RB Kills", ImVec2(107, 440), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"kills");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iRebirthKills);
						}
						//
						ImGui::KnobSliderSCP("RB Deaths", &JaysModz->msettings.iRebirthDeaths, 1, 9999999, ImVec2(367, 330), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set RB Deaths", ImVec2(337, 440), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br_rebirth");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"deaths");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iRebirthDeaths);
						}
						ImGui::PopFont();
					}
					if (JaysModz->msettings.bMiscBRSelected)
					{
						ImGui::PushFont(Body2);
						ImGui::CenterText("- Click and Hold on the Circle Slider and Move UP/DOWN to Change Value -", 100, FALSE, FALSE);
						ImGui::KnobSliderSCP("BR Score", &JaysModz->msettings.iBRScore, 1, 9999999, ImVec2(37, 180), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Score", &MiscVars::bBRScore, ImVec2(7, 290), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"score");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRScore);
						}
						//
						ImGui::KnobSliderSCP("BR GP", &JaysModz->msettings.iBRGamesPlayed, 1, 9999999, ImVec2(183, 180), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Game Played", ImVec2(153, 290), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"gamesPlayed");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRGamesPlayed);
						}
						//
						ImGui::KnobSliderSCP("BR TP", &JaysModz->msettings.iBRTimePlayed, 1, 9999999, ImVec2(330, 180), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Time Played", ImVec2(300, 290), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"timePlayed");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRTimePlayed);
						}
						//
						ImGui::KnobSliderSCP("BR Wins", &JaysModz->msettings.iBRWins, 1, 9999999, ImVec2(477, 180), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Wins", ImVec2(447, 290), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"wins");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRWins);
						}
						//
						ImGui::KnobSliderSCP("BR Top 5", &JaysModz->msettings.iBRTop5, 1, 9999999, ImVec2(37, 330), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Top 5", ImVec2(7, 440), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"topFive");
							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRTop5);

						}
						//
						ImGui::KnobSliderSCP("BR Kills", &JaysModz->msettings.iBRKills, 1, 9999999, ImVec2(183, 330), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Kills", ImVec2(153, 440), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"kills");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRKills);
						}
						//
						ImGui::KnobSliderSCP("BR Deaths", &JaysModz->msettings.iBRDeaths, 1, 9999999, ImVec2(330, 330), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Deaths", ImVec2(300, 440), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"deaths");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRDeaths);
						}
						//
						ImGui::KnobSliderSCP("BR Downs", &JaysModz->msettings.iBRDowns, 1, 9999999, ImVec2(477, 330), TRUE, FALSE);
						if (ImGui::Button(xorstr_("Set Downs", ImVec2(447, 440), ImVec2(125, 18))))
						{
							char context[255];
							char state[255];

							__int64 ddl_file = Com_DDL_LoadAsset((__int64)"ddl/mp/playerdata.ddl");

							CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 0);

							DDL_GetRootState((__int64)state, ddl_file);

							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"rankedMatchData");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"playerStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"modeStats");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"br");
							DDL_MoveToName((__int64)state, (__int64)state, (__int64)"downs");

							DDL_SetInt((__int64)state, (__int64)context, (unsigned int)JaysModz->msettings.iBRDowns);
						}
						ImGui::PopFont();
					}
				} ImGui::EndChild();
				ImGui::PopStyleColor();
			}
			ImGui::EndChild();
		} 

	}


