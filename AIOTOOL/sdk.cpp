#include "sdk.h"

HWND process::hwnd;
__int64 Com_DDL_LoadAsset(__int64 file) {
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.ddl_loadasset;
	return ((__int64 (*)(__int64))address)(file);
}

__int64 DDL_GetRootState(__int64 state, __int64 file) {
	uintptr_t address =JaysModz->baseModule + JaysModz->goffsets.ddl_getrootstate;
	return ((__int64 (*)(__int64, __int64))address)(state, file);
}

bool CL_PlayerData_GetDDLBuffer(__int64 context, int controllerindex, int stats_source, unsigned int statsgroup) {
	uintptr_t address =JaysModz->baseModule + JaysModz->goffsets.ddl_getdllbuffer;
	return ((bool (*)(__int64, int, int, unsigned int))address)(context, controllerindex, stats_source, statsgroup);
}
bool ParseShit(const char* a, const char** b, const int c, int* d)
{
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.a_parse;
	return ((bool (*)(const char* a, const char** b, const int c, int* d))address)(a, b, c,d);

}
char DDL_MoveToPath(__int64* fromState, __int64* toState, int depth, const char** path) {
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.ddl_movetopath;
	return ((char (*)(__int64* fromState, __int64* toState, int depth, const char** path))address)(fromState, toState, depth, path);
	
}
bool DDL_Parse(const char* pStr, const char** navStrings2, const int navStringMax, int* navStringCount)
{
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.ddl_parse;
	return ((bool (*)(const char* pStr, const char** navStrings2, const int navStringCount, int* param_4))address)(pStr, navStrings2, navStringMax, navStringCount);
}
__int64 DDL_MoveToName(__int64 fstate, __int64 tstate, __int64 path) {
	uintptr_t address =JaysModz->baseModule + JaysModz->goffsets.ddl_movetoname;
	return ((__int64 (*)(__int64, __int64, __int64))address)(fstate, tstate, path);
}

char DDL_SetInt(__int64 fstate, __int64 context, unsigned int value) {
	uintptr_t address =JaysModz->baseModule + JaysModz->goffsets.ddl_setint;
	return ((char (*)(__int64, __int64, unsigned int))address)(fstate, context, value);
}
char DDL_SetEnum(__int64 fstate, __int64 context, const char* value) {
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.ddl_setenum;
	return ((char (*)(__int64, __int64, const char*))address)(fstate, context, value);
}
char DDL_SetString(__int64 fstate, __int64 context, const char* value) {
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.ddl_setstring;
	return ((char (*)(__int64, __int64, const char*))address)(fstate, context, value);
}
char DDL_SetInt2(__int64* fstate, __int64* context, int value) {
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.ddl_setint;
	return ((char (*)(__int64*, __int64*, unsigned int))address)(fstate, context, value);
}
int DDL_GetInt(__int64* fstate, __int64* context) {
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.ddl_getint;
	return ((int (*)(__int64*, __int64*))address)(fstate, context);
}
BOOL CALLBACK process::EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);
	if (dwPid == lParam)
	{
		hwnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND process::get_process_window()
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, GetCurrentProcessId());

	if (hwnd == NULL)
		Exit();

	return hwnd;
}

HWND process::get_process_window(DWORD procID)
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, procID);

	if (hwnd == NULL)
		Exit();

	return hwnd;
}
void RenderLine(ImVec2 a, ImVec2 b, ImColor color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(a, b, color, thickness);
}
void draw_line(const ImVec2& from, const ImVec2& to, ImColor color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	float a = (color >> 24) & 0xff;
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;
	window->DrawList->AddLine(from, to, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
}
void draw_crosshair()
{
	constexpr long crosshair_size = 10.0f;
	ImVec2 center = ImVec2(WND_SIZEX / 2, WND_SIZEY / 2);
	RenderLine(ImVec2((center.x), (center.y) - crosshair_size), ImVec2((center.x), (center.y) + crosshair_size), JaysModz->msettings.crosshair_color, 1.5f);
	RenderLine(ImVec2((center.x) - crosshair_size, (center.y)), ImVec2((center.x) + crosshair_size, (center.y)), JaysModz->msettings.crosshair_color, 1.5f);
}
void equipOpMP2()
{
	char context[255];
	char state[255];
	int string_count;
	char* str[16]{};
	const char* mode = "";
	char buffer[200];
	if (JaysModz->msettings.iGameMode4 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	if (JaysModz->msettings.iGameMode4 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("customizationSetup.operators.1"));
	ParseShit(buffer, (const char**)str, 16, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetEnum((__int64)state, (__int64)context, "default_eastern");
	}
}
void equipOpMP1()
{
	char context[255];
	char state[255];
	int string_count;
	char* str[16]{};
	const char* mode = "";
	char buffer[200];
	if (JaysModz->msettings.iGameMode4 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	if (JaysModz->msettings.iGameMode4 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("customizationSetup.operators.0"));
	ParseShit(buffer, (const char**)str, 16, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetEnum((__int64)state, (__int64)context, "default_western");
	}
}
void setopp(int op)
{
	//Beep(200, 200);
	equipOpMP1();
	char context[255];
	char state[255];
	int string_count;
	char* str[16]{};
	const char* mode = "";
	char buffer[200];

	if (JaysModz->msettings.iGameMode4 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	if (JaysModz->msettings.iGameMode4 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.default_western.skin"));
	ParseShit(buffer, (const char**)str, 16, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetInt((__int64)state, (__int64)context, op);
	}

}

void setoppa(int op)
{
	equipOpMP2();
	char context[255];
	char state[255];
	int string_count;
	char* str[16]{};
	const char* mode = "";
	char buffer[200];

	if (JaysModz->msettings.iGameMode4 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	if (JaysModz->msettings.iGameMode4 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.default_eastern.skin"));
	ParseShit(buffer, (const char**)str, 16, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetInt((__int64)state, (__int64)context, op);
	}

}

void SetCamo(int Class, int Weapon, int Camo)
{
	char context[255];
	char state[255];
	int navStringCount;
	char* navStrings[16]{};
	const char* mode = "";

	if (JaysModz->msettings.iGameMode == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (JaysModz->msettings.iGameMode == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}

	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);

	DDL_GetRootState((__int64)state, ddl_file);
	char buffer[200];
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.%i.camo"), Class, Weapon);
	ParseShit(buffer, (const char**)navStrings, 16, &navStringCount);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
	{
		DDL_SetInt((__int64)state, (__int64)context, Camo);
	}
}

void CopyWeapon(int Class)
{
	char context[255];
	char state[255];
	char context2[255];
	char state2[255];
	int navStringCount;
	char* navStrings[16]{};
	int navStringCount2;
	char* navStrings2[16]{};
	const char* mode = "";
	int wep = 0;
	if (JaysModz->msettings.iGameMode2 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (JaysModz->msettings.iGameMode2 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}

	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);

	DDL_GetRootState((__int64)state, ddl_file);
	char buffer[200];
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.weapon"), Class);
	ParseShit(buffer, (const char**)navStrings, 16, &navStringCount);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
	{
		wep = DDL_GetInt((__int64*)&state, (__int64*)&context);

	}
	if (JaysModz->msettings.iGameMode2 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context2, 0, 0, 3);
	}
	else if (JaysModz->msettings.iGameMode2 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context2, 0, 0, 5);
	}
	__int64 ddl_file2 = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state2, ddl_file2);
	char buffer2[200];
	memset(buffer2, 0, 200);
	sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.weapon"), Class);
	ParseShit(buffer2, (const char**)navStrings2, 16, &navStringCount2);
	if (DDL_MoveToPath((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
	{
		DDL_SetInt2((__int64*)&state2, (__int64*)&context2, wep);
	}
}

void setOperators(const char operators[255], int operatorid)
{
	char context[255];
	char state[255];
	int string_count;
	char* str[16]{};
	const char* mode = "";
	char buffer[200];

	if (JaysModz->msettings.iGameMode3 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (JaysModz->msettings.iGameMode3 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.%s.skin"), operators);
	DDL_Parse(buffer, (const char**)str, 32, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetInt((__int64)state, (__int64)context, operatorid);
	}
}

void SetClassName(int classSection, char* className)
{
	char context[255];
	char state[255];
	int navStringCount;
	char* navStrings[16]{};
	const char* mode = "";

	if (JaysModz->msettings.iGameMode3 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (JaysModz->msettings.iGameMode3 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}

	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);

	DDL_GetRootState((__int64)state, ddl_file);
	char buffer[200];
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.name"), classSection);
	ParseShit(buffer, (const char**)navStrings, 16, &navStringCount);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
	{
		DDL_SetString((__int64)state, (__int64)context, className);
	}
}

void SetRebirthStats(const char* category, int* value)
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
	DDL_MoveToName((__int64)state, (__int64)state, (__int64)category);

	DDL_SetInt((__int64)state, (__int64)context, (unsigned int)value);
}

void SetupRebirthSetStats(const char* category, bool* featureBool, int* value)
{
	if (*featureBool)
	{
		SetRebirthStats(category, value);
		*featureBool = false;
	}
}

void SetupBRStats(const char* category, int* value)
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
	DDL_MoveToName((__int64)state, (__int64)state, (__int64)category);

	DDL_SetInt((__int64)state, (__int64)context, (unsigned int)value);
}

void SetupBRSetStats(const char* category, bool* featureBool, int* value)
{
	if (*featureBool)
	{
		SetupBRStats(category, value);
		*featureBool = false;
	}
}
struct GfxSceneHudOutlineInfo
{
	unsigned int color;
	float scopeStencil;
	bool drawOccludedPixels;
	bool drawNonOccludedPixels;
	bool fill;
	bool useAlternateColor;
	bool forSpectator;
	bool specialActive;
	unsigned __int8 renderMode;
	unsigned __int8 lineWidth;
	unsigned __int8 temperatureSet;
	unsigned int mapEntLookup;
	float temperatureBase;
	float temperatureScale;
	float characterEVOffset;
};
struct GfxSceneEntityMutableShaderData
{
	char pd[0x88];
	GfxSceneHudOutlineInfo hudOutlineInfo;
};

unsigned char tempRainbow[4] = { 255, 0, 0, 0 };
unsigned __int64 FuncOriginal;
void updateRainbowColor() {
	int stage = tempRainbow[3];
	switch (stage) {
	case 0:        tempRainbow[2] += 5;        if (tempRainbow[2] == 255)            tempRainbow[3] = 1;        break;
	case 1:        tempRainbow[0] -= 5;        if (tempRainbow[0] == 0)            tempRainbow[3] = 2;        break;
	case 2:        tempRainbow[1] += 5;        if (tempRainbow[1] == 255)            tempRainbow[3] = 3;        break;
	case 3:        tempRainbow[2] -= 5;        if (tempRainbow[2] == 0)            tempRainbow[3] = 4;        break;
	case 4:        tempRainbow[0] += 5;        if (tempRainbow[0] == 255)            tempRainbow[3] = 5;        break;
	case 5:        tempRainbow[1] -= 5;        if (tempRainbow[1] == 0)            tempRainbow[3] = 0;        break;
	}
}
void hookFunc(__int64 a1, __int64 a2, unsigned int entnum, unsigned int renderFlags, GfxSceneEntityMutableShaderData* a3, __int64 a4, float materialTime)
{

	//
	if ((*(BYTE*)a2 == 1))
	{
		if (renderFlags > 513) //0 = loot
		{
			if (entnum < 201)
			{
				if (JaysModz->msettings.visibleOutlines)
					a3->hudOutlineInfo.drawNonOccludedPixels = true;
				if (JaysModz->msettings.notVisibleOutlines)
					a3->hudOutlineInfo.drawOccludedPixels = true;
				if (JaysModz->msettings.chamFill)
					a3->hudOutlineInfo.fill = true;

				a3->hudOutlineInfo.renderMode = 0;

				//a3->hudOutlineInfo.color = 0xFFFF00FF;
				if (JaysModz->msettings.rgbChams) {
					a3->hudOutlineInfo.color = JaysModz->msettings.chamColorRGB;
				}
				else
				{
					a3->hudOutlineInfo.color = JaysModz->msettings.playerColor;
				}
				a3->hudOutlineInfo.lineWidth = JaysModz->msettings.lineWidthNum;
			}
		}
	}
	if (JaysModz->msettings.lootChams)
	{
		if (renderFlags == 0)
		{
			if (JaysModz->msettings.visibleOutlines)
				a3->hudOutlineInfo.drawNonOccludedPixels = true;
			if (JaysModz->msettings.notVisibleOutlines)
				a3->hudOutlineInfo.drawOccludedPixels = true;
			if (JaysModz->msettings.chamFill)
				a3->hudOutlineInfo.fill = true;

			a3->hudOutlineInfo.renderMode = 0;

			//a3->hudOutlineInfo.color = 0xFFFF00FF;
			if (JaysModz->msettings.rgbChams)
			{
				a3->hudOutlineInfo.color = JaysModz->msettings.chamColorRGB;
			}
			else
			{
				a3->hudOutlineInfo.color = JaysModz->msettings.lootColor;
			}
			a3->hudOutlineInfo.lineWidth = JaysModz->msettings.lineWidthNum;
		}
	}
	if (FuncOriginal)
		((void(*)(...))FuncOriginal)(a1, a2, entnum, renderFlags, a3, a4, materialTime);
}
void chamCheck()
{
	if (JaysModz->msettings.chams == true)
	{
		if (JaysModz->msettings.chamHooked == false)
		{
			if (*(int*)(JaysModz->baseModule + JaysModz->goffsets.playerCountOffset) >= 2)
			{
				if (*(int*)(JaysModz->baseModule + JaysModz->goffsets.inGameOffset) > 2)
				{
					JaysModz->msettings.chamHooked = true;
					//notify::insert({ toast_type::toast_type_success, 3000, "Chams Hooked!" });
					//NOTIFY PLAYER CHAMS HAVE HOOKED
					MH_CreateHook((LPVOID*)(JaysModz->baseModule + JaysModz->goffsets.chamOffset), &hookFunc, (LPVOID*)&FuncOriginal);
					MH_EnableHook(MH_ALL_HOOKS);

				}
			}
		}
		if (JaysModz->msettings.chamHooked == true)
		{
			if (*(int*)(JaysModz->baseModule + JaysModz->goffsets.playerCountOffset) <= 2)
			{
				if (*(int*)(JaysModz->baseModule + JaysModz->goffsets.inGameOffset) < 2)
				{
					JaysModz->msettings.chams = false;
					JaysModz->msettings.chamHooked = false;
					//notify::insert({ toast_type::toast_type_warning, 3000, "Chams Turned Off to Prevent Crashing!\nYou can safely re-enable." });
					//NOTIFY PLAYER OF THE ABOVE
					//THIS ONLY HAPPENS WHEN LEAVING A MATCH
					MH_DisableHook((LPVOID*)(JaysModz->baseModule + JaysModz->goffsets.chamOffset));

				}
			}
		}
	}
	else
	{
		if (JaysModz->msettings.chamHooked == true)
		{
			JaysModz->msettings.chamHooked = false;
			MH_DisableHook((LPVOID*)(JaysModz->baseModule + JaysModz->goffsets.chamOffset));
		}
	}

}

namespace EngineFeatures
{	
	void draw_line(const ImVec2& from, const ImVec2& to, C_Color color, float thickness)
	{
		ImGui::GetBackgroundDrawList()->AddLine(from, to, color.GetU32(), thickness);
	}
	
	bool is_key_down(int vk_key)
	{
		return ((GetAsyncKeyState(vk_key) & 0x8000) ? 1 : 0);
	}
	
	void EnableFeatures()
	{
		// Write Skip WZ Tut.
		if (JaysModz->msettings.b_tut)
		{
			dvar_set2(xorstr_("LSPSKLPNQT"), 1);
		}
		else if (!JaysModz->msettings.b_tut)
		{
			dvar_set2(xorstr_("LSPSKLPNQT"), 0);
		}
		// Write FPS Boost.
		if (JaysModz->msettings.b_fps)
		{
			dvar_set2("OPOTTRRNQ", 0);
			dvar_set2("NNRQTQNLRL", 0);
			dvar_set2("NNTOQLMSLO", 3);
			dvar_set2("NTROOKOSPM", 3);
			dvar_set2("NNKRMTSNPL", 0);
			dvar_set2("MOLLKMTMRS", 0);
			dvar_set2("MQOPRPQLQL", 0);
			dvar_set2("NLNKQNROQM", 0);
			dvar_set2("LTOKRMRTMM", 0);
		}
		else if (!JaysModz->msettings.b_fps)
		{
			// Disable?
		}
		// Write Force Start Priv WZ Match.
		if (JaysModz->msettings.b_priv)
		{
			dvar_set2(xorstr_("LOQQOSNQKN"), 1);
			dvar_set2(xorstr_("PKMLMMTSN"), 1);
		}
		else if (!JaysModz->msettings.b_priv)
		{
			dvar_set2(xorstr_("LOQQOSNQKN"), 0);
			dvar_set2(xorstr_("PKMLMMTSN"), 0);
		}
		// Write Owner Check.
		if (JaysModz->msettings.b_owner)
		{
			dvar_set2(xorstr_("NRQQOMLOQL"), 0);
			dvar_set2(xorstr_("RRTLRKKTT"), 0);
			dvar_set2(xorstr_("MKQPRPLQKL"), 0);
		}
		else if (!JaysModz->msettings.b_owner)
		{
			dvar_set2(xorstr_("NRQQOMLOQL"), 1);
			dvar_set2(xorstr_("RRTLRKKTT"), 1);
			dvar_set2(xorstr_("MKQPRPLQKL"), 1);
		}
		// Write Profanity Name Bypass.
		if (JaysModz->msettings.b_name)
		{
			dvar_set2(xorstr_("PLTMTSLKT"), 0);
		}
		else if (!JaysModz->msettings.b_name)
		{
			dvar_set2(xorstr_("PLTMTSLKT"), 1);
		}
		// Write No Flash Bang.
		if (JaysModz->msettings.b_no_flashbang)
		{
			dvar_set2("cg_drawShellshock", 0);
		}
		else if (!JaysModz->msettings.b_no_flashbang)
		{
			dvar_set2("cg_drawShellshock", 1);
		}
		// Write No Stun.
		if (JaysModz->msettings.b_no_stun)
		{
			dvar_set2("MMQKQOSTNS", 1);
		}
		else if (!JaysModz->msettings.b_no_stun)
		{
			dvar_set2("MMQKQOSTNS", 0);
		}
		// Write Bright.
		if (JaysModz->msettings.b_brightmax)
		{
			dvar_set2("NQKKOONQPR", 0);
			dvar_set2("MTLMSQMNTR", 0);
			dvar_set2("RNPPKQOTN", 0);
			dvar_set2("LKOLRONRNQ", 0);
			dvar_set2("LTOKRMRTMM", 0);
		}
		else if (!JaysModz->msettings.b_brightmax)
		{
			dvar_set2("NQKKOONQPR", 1);
			dvar_set2("MTLMSQMNTR", 1);
			dvar_set2("RNPPKQOTN", 1);
			dvar_set2("LKOLRONRNQ", 1);
			dvar_set2("LTOKRMRTMM", 1);
		}
		// Write No Fog.
		if (JaysModz->msettings.b_no_fog)
		{
			dvar_set2("LTOKRMRTMM", 0);
		}
		else if (!JaysModz->msettings.b_no_fog)
		{
			dvar_set2("LTOKRMRTMM", 1);
		}
		// Write Third Person.
		if (JaysModz->msettings.b_Thirdperson)
		{
			dvar_set2("NOSLRNTRKL", 1);
		}
		else if (!JaysModz->msettings.b_Thirdperson)
		{
			dvar_set2("NOSLRNTRKL", 0);
		}
		// Write Spectator Third Person.
		if (JaysModz->msettings.b_sThirdperson)
		{
			dvar_set2("LKNNQKNTS", 1);
		}
		else if (!JaysModz->msettings.b_sThirdperson)
		{
			dvar_set2("LKNNQKNTS", 0);
		}
		// Write Dynamic Third Person.
		if (JaysModz->msettings.b_dynamic3p)
		{
			if (is_key_down(VK_RBUTTON) || is_key_down(VK_GAMEPAD_LEFT_TRIGGER))
			{
				dvar_set2("NOSLRNTRKL", 0);
			}
			else
			{
				dvar_set2("NOSLRNTRKL", 1);
			}
		}
		else if (!JaysModz->msettings.b_dynamic3p)
		{
			// Disbale?
		}
		// Write No Shield Shake.
		if (JaysModz->msettings.b_shield)
		{
			dvar_set2("LQKTTRTSNS", 0);
		}
		else if (!JaysModz->msettings.b_shield)
		{
			dvar_set2("LQKTTRTSNS", 1);
		}
		// Write Unlimited Sprint.
		if (JaysModz->msettings.b_sprint)
		{
			dvar_set2("MSOOMPMPQS", 1);
		}
		else if (!JaysModz->msettings.b_sprint)
		{
			dvar_set2("MSOOMPMPQS", 0);
		}
		// Write Heart Cheat.
		if (JaysModz->msettings.b_heart)
		{
			dvar_set2("NSKNMSMOLP", 2);
			dvar_set2("NLLRSSOQMQ", 10000);
		}
		else if (!JaysModz->msettings.b_heart)
		{
			// Disable?
		}
		// Write No Gun.
		if (JaysModz->msettings.b_gun)
		{
			dvar_set2("SROLTPQLK", 0);
		}
		else if (!JaysModz->msettings.b_gun)
		{
			dvar_set2("SROLTPQLK", 1);
		}
		// Write Fuck Your View up.
		if (JaysModz->msettings.b_fuckview)
		{
			dvar_set2("LLLRKRROOP", 1);
		}
		else if (!JaysModz->msettings.b_fuckview)
		{
			dvar_set2("LLLRKRROOP", 0);
		}
		// Write FOV.
		if (JaysModz->msettings.b_fov)
		{
			if (JaysModz->msettings.iFovValue == 1)
			{
				dvar_set2("NSSLSNKPN", 1.f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 2)
			{
				dvar_set2("NSSLSNKPN", 1.1f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 3)
			{
				dvar_set2("NSSLSNKPN", 1.2f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 4)
			{
				dvar_set2("NSSLSNKPN", 1.3f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 5)
			{
				dvar_set2("NSSLSNKPN", 1.4f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 6)
			{
				dvar_set2("NSSLSNKPN", 1.5f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 7)
			{
				dvar_set2("NSSLSNKPN", 1.6f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 8)
			{
				dvar_set2("NSSLSNKPN", 1.7f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 9)
			{
				dvar_set2("NSSLSNKPN", 1.8f);
				JaysModz->msettings.b_fov = false;
			}
			if (JaysModz->msettings.iFovValue == 10)
			{
				dvar_set2("NSSLSNKPN", 2.f);
				JaysModz->msettings.b_fov = false;
			}
		}
		// Write Mini Map Size.
		if (JaysModz->msettings.b_map)
		{
			if (JaysModz->msettings.iMiniMapValue == 1)
			{
				dvar_set2("MKMRRLNRTM", 1.f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 2)
			{
				dvar_set2("MKMRRLNRTM", 1.1f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 3)
			{
				dvar_set2("MKMRRLNRTM", 1.2f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 4)
			{
				dvar_set2("MKMRRLNRTM", 1.3f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 5)
			{
				dvar_set2("MKMRRLNRTM", 1.4f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 6)
			{
				dvar_set2("MKMRRLNRTM", 1.5f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 7)
			{
				dvar_set2("MKMRRLNRTM", 1.6f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 8)
			{
				dvar_set2("MKMRRLNRTM", 1.7f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 9)
			{
				dvar_set2("MKMRRLNRTM", 1.8f);
				JaysModz->msettings.b_map = false;
			}
			if (JaysModz->msettings.iMiniMapValue == 10)
			{
				dvar_set2("MKMRRLNRTM", 2.f);
				JaysModz->msettings.b_map = false;
			}
		}
		// Write Preset Clan Tag.
		if (JaysModz->msettings.bSetPresetClanTag)
		{
			CL_PlayerData_SetCustomClanTag(JaysModz->msettings.sPresetClanTag.c_str());
			JaysModz->msettings.bSetPresetClanTag = false;
		}
		// Write Custom Clan Tag.
		if (JaysModz->msettings.bSetCustomClanTag)
		{
			JaysModz->msettings.sCustomClanTag = JaysModz->msettings.cCustomClanTagBuf;
			CL_PlayerData_SetCustomClanTag(JaysModz->msettings.sCustomClanTag.c_str());
			JaysModz->msettings.bSetCustomClanTag = false;
		}

		// Write op swap.
		if (JaysModz->msettings.bSetOPWZ)
		{
			// Writing MP Guns.
			if (!JaysModz->msettings.bMiscMPWZOS)
			{
				JaysModz->msettings.iGameMode4 = 0;
				setopp(JaysModz->msettings.iOPSelection);
				JaysModz->msettings.bSetOPWZ = false;
			}
			else // Writing WZ Guns.
			{
				JaysModz->msettings.iGameMode4 = 1;
				setopp(JaysModz->msettings.iOPSelection);
				JaysModz->msettings.bSetOPWZ = false;
			}
		}

		// Write op swap.
		if (JaysModz->msettings.bSetOPMP1)
		{
			// Writing MP Guns.
			if (!JaysModz->msettings.bMiscMPWZOS)
			{
				JaysModz->msettings.iGameMode4 = 0;
				setopp(JaysModz->msettings.iOPSelection);
				JaysModz->msettings.bSetOPMP1 = false;
			}
			else // Writing WZ Guns.
			{
				JaysModz->msettings.iGameMode4 = 1;
				setopp(JaysModz->msettings.iOPSelection);
				JaysModz->msettings.bSetOPMP1 = false;
			}
		}

		// Write op swap.
		if (JaysModz->msettings.bSetOPMP2)
		{
			// Writing MP Guns.
			if (!JaysModz->msettings.bMiscMPWZOS)
			{
				JaysModz->msettings.iGameMode4 = 0;
				setoppa(JaysModz->msettings.iOPSelection);
				JaysModz->msettings.bSetOPMP2 = false;
			}
			else // Writing WZ Guns.
			{
				JaysModz->msettings.iGameMode4 = 1;
				setoppa(JaysModz->msettings.iOPSelection);
				JaysModz->msettings.bSetOPMP2 = false;
			}
		}

		// Write Double Gun.
		if (JaysModz->msettings.bSetDoubleGun)
		{
			// Writing MP Guns.
			if (!JaysModz->msettings.bMiscMPWZDG)
			{
				JaysModz->msettings.iGameMode2 = 0;
				CopyWeapon(JaysModz->msettings.iLoadoutSelection);
				JaysModz->msettings.bSetDoubleGun = false;
			}
			else // Writing WZ Guns.
			{
				JaysModz->msettings.iGameMode2 = 1;
				CopyWeapon(JaysModz->msettings.iLoadoutSelection);
				JaysModz->msettings.bSetDoubleGun = false;
			}
		}
		// Write Double Gun All.
		if (JaysModz->msettings.bSetDoubleGunAll)
		{
			// Writing MP Guns.
			if (!JaysModz->msettings.bMiscMPWZDG)
			{
				JaysModz->msettings.iGameMode2 = 0;
				CopyWeapon(0);
				CopyWeapon(1);
				CopyWeapon(2);
				CopyWeapon(3);
				CopyWeapon(4);
				CopyWeapon(5);
				CopyWeapon(6);
				CopyWeapon(7);
				CopyWeapon(8);
				CopyWeapon(9);
				CopyWeapon(10);
				JaysModz->msettings.bSetDoubleGunAll = false;
			}
			else // Writing WZ Guns.
			{
				JaysModz->msettings.iGameMode2 = 1;
				CopyWeapon(0);
				CopyWeapon(1);
				CopyWeapon(2);
				CopyWeapon(3);
				CopyWeapon(4);
				CopyWeapon(5);
				CopyWeapon(6);
				CopyWeapon(7);
				CopyWeapon(8);
				CopyWeapon(9);
				CopyWeapon(10);
				JaysModz->msettings.bSetDoubleGunAll = false;
			}
		}
		// Write Set Camo.
		if (JaysModz->msettings.bSetCamo)
		{
			if (!JaysModz->msettings.bMiscMPWZCamoClass)
			{
				JaysModz->msettings.iGameMode = 0;
				SetCamo(JaysModz->msettings.iCamoLoadoutSelection, JaysModz->msettings.iWeaponSelection, JaysModz->msettings.iCamoSelection);
				JaysModz->msettings.bSetCamo = false;
			}
			else
			{
				JaysModz->msettings.iGameMode = 1;
				SetCamo(JaysModz->msettings.iCamoLoadoutSelection, JaysModz->msettings.iWeaponSelection, JaysModz->msettings.iCamoSelection);
				JaysModz->msettings.bSetCamo = false;
			}
		}
		// Write Set Camo All.
		if (JaysModz->msettings.bSetCamoAll)
		{
			if (!JaysModz->msettings.bMiscMPWZCamoClass)
			{
				JaysModz->msettings.iGameMode = 0;
				SetCamo(0, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(0, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(1, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(1, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(2, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(2, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(3, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(3, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(4, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(4, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(5, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(5, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(6, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(6, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(7, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(7, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(8, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(8, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(9, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(9, 1, JaysModz->msettings.iCamoSelection);
				JaysModz->msettings.bSetCamoAll = false;
			}
			else
			{
				JaysModz->msettings.iGameMode = 1;
				SetCamo(0, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(0, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(1, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(1, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(2, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(2, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(3, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(3, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(4, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(4, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(5, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(5, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(6, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(6, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(7, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(7, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(8, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(8, 1, JaysModz->msettings.iCamoSelection);
				SetCamo(9, 0, JaysModz->msettings.iCamoSelection);
				SetCamo(9, 1, JaysModz->msettings.iCamoSelection);
				JaysModz->msettings.bSetCamoAll = false;
			}
		}
		// Write Class Name.
		if (JaysModz->msettings.bSetClassName)
		{
			if (!JaysModz->msettings.bMiscMPWZClassName)
			{
				JaysModz->msettings.iGameMode3 = 0;
				SetClassName(JaysModz->msettings.iClassNameSelection, JaysModz->msettings.cClassEditorBuf);
				JaysModz->msettings.bSetClassName = false;
			}
			else
			{
				JaysModz->msettings.iGameMode3 = 1;
				SetClassName(JaysModz->msettings.iClassNameSelection, JaysModz->msettings.cClassEditorBuf);
				JaysModz->msettings.bSetClassName = false;
			}
		}
		// Write Class Name All.
		if (JaysModz->msettings.bSetClassNameAll)
		{
			if (!JaysModz->msettings.bMiscMPWZClassName)
			{
				JaysModz->msettings.iGameMode3 = 0;
				SetClassName(0, JaysModz->msettings.cClassEditorBuf);
				SetClassName(1, JaysModz->msettings.cClassEditorBuf);
				SetClassName(2, JaysModz->msettings.cClassEditorBuf);
				SetClassName(3, JaysModz->msettings.cClassEditorBuf);
				SetClassName(4, JaysModz->msettings.cClassEditorBuf);
				SetClassName(5, JaysModz->msettings.cClassEditorBuf);
				SetClassName(6, JaysModz->msettings.cClassEditorBuf);
				SetClassName(7, JaysModz->msettings.cClassEditorBuf);
				SetClassName(8, JaysModz->msettings.cClassEditorBuf);
				SetClassName(9, JaysModz->msettings.cClassEditorBuf);
				JaysModz->msettings.bSetClassNameAll = false;
			}
			else
			{
				JaysModz->msettings.iGameMode3 = 1;
				SetClassName(0, JaysModz->msettings.cClassEditorBuf);
				SetClassName(1, JaysModz->msettings.cClassEditorBuf);
				SetClassName(2, JaysModz->msettings.cClassEditorBuf);
				SetClassName(3, JaysModz->msettings.cClassEditorBuf);
				SetClassName(4, JaysModz->msettings.cClassEditorBuf);
				SetClassName(5, JaysModz->msettings.cClassEditorBuf);
				SetClassName(6, JaysModz->msettings.cClassEditorBuf);
				SetClassName(7, JaysModz->msettings.cClassEditorBuf);
				SetClassName(8, JaysModz->msettings.cClassEditorBuf);
				SetClassName(9, JaysModz->msettings.cClassEditorBuf);

				JaysModz->msettings.bSetClassNameAll = false;
			}
		}
		// Write Rebirth Stats.
		SetupRebirthSetStats("wins", &JaysModz->msettings.bRebirthWins, &JaysModz->msettings.iRebirthWins);
		SetupRebirthSetStats("topFive", &JaysModz->msettings.bRebirthWins, &JaysModz->msettings.iRebirthTop5);
		SetupRebirthSetStats("kills", &JaysModz->msettings.bRebirthWins, &JaysModz->msettings.iRebirthKills);
		SetupRebirthSetStats("deaths", &JaysModz->msettings.bRebirthWins, &JaysModz->msettings.iRebirthDeaths);
		// Write BR Stats.
		SetupBRSetStats("score", &JaysModz->msettings.bBRScore, &JaysModz->msettings.iBRScore);
		SetupBRSetStats("gamesPlayed", &JaysModz->msettings.bBRGamesPlayed, &JaysModz->msettings.iBRGamesPlayed);
		SetupBRSetStats("timePlayed", &JaysModz->msettings.bBRTimePlayed, &JaysModz->msettings.iBRTimePlayed);
		SetupBRSetStats("wins", &JaysModz->msettings.bBRWins, &JaysModz->msettings.iBRWins);
		SetupBRSetStats("topFive", &JaysModz->msettings.bBRTop5, &JaysModz->msettings.iBRTop5);
		SetupBRSetStats("kills", &JaysModz->msettings.bBRKills, &JaysModz->msettings.iBRKills);
		SetupBRSetStats("deaths", &JaysModz->msettings.bBRDeaths, &JaysModz->msettings.iBRDeaths);
		SetupBRSetStats("downed", &JaysModz->msettings.bBRDowns, &JaysModz->msettings.iBRDowns);
		// Write Unlock All.
		if (JaysModz->msettings.b_unlock)
		{
			unlock();
			JaysModz->msettings.b_unlock = false;
		}
		// Draw Crosshair.
		if (JaysModz->msettings.chrosshair)
		{
			draw_crosshair();
		}
	}
}

namespace g_game
{
	void main_loop(ImFont* font);
	void ui_header()
	{
		if (JaysModz->msettings.b_menuEnable)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.65f));
			ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
			int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 4;
			int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
			int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 4;
			int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
		}
		ImGuiIO& io = ImGui::GetIO();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
	}

	void ui_end()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
	}


	void init(ImFont* font)
	{
		ui_header();
		main_loop(font);
		updateRainbowColor();
		JaysModz->msettings.chamColorRGB = ImGui::ColorConvertFloat4ToU32(ImVec4((float)tempRainbow[0] / 255, (float)tempRainbow[1] / 255, (float)tempRainbow[2] / 255, 1.0f));
		chamCheck();
		ui_end();
	}
	void main_loop(ImFont* font)
	{
		EngineFeatures::EnableFeatures();
	}
}


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



void CL_PlayerData_SetCustomClanTag(const char* clanTag)
{
	//74 ?? 48 8d 15 ?? ?? ?? ?? 8b cf e8 ?? ?? ?? ?? 48 8b 5c 24 30
	uintptr_t address = JaysModz->baseModule + JaysModz->goffsets.clantag_offset;
	((void(*)(int, const char*))address)(0, clanTag);
}

dvar_s* Dvar_FindVarByName(const char* dvarName)
{
	//[48 83 EC 48 49 8B C8 E8 ?? ?? ?? ?? + 0x7] resolve call.
	return reinterpret_cast<dvar_s * (__fastcall*)(const char* dvarName)>(JaysModz->baseModule + JaysModz->goffsets.Dvar_FindVarByName)(dvarName);
}

uintptr_t Dvar_SetBool_Internal(dvar_s* a1, bool a2)
{
	//E8 ? ? ? ? 80 3D ? ? ? ? ? 4C 8D 35 ? ? ? ? 74 43 33 D2 F7 05 ? ? ? ? ? ? ? ? 76 2E
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, bool a2)>(JaysModz->baseModule + JaysModz->goffsets.Dvar_SetBoolInternal)(a1, a2);
}

uintptr_t Dvar_SetInt_Internal(dvar_s* a1, unsigned int a2)
{
	//40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 0F B6 41 09 48 8B D9
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, unsigned int a2)>(JaysModz->baseModule + JaysModz->goffsets.Dvar_SetInt_Internal)(a1, a2);
}

uintptr_t Dvar_SetBoolByName(const char* dvarName, bool value)
{
	//"48 89 ? ? ? 57 48 81 EC ? ? ? ? 0F B6 ? 48 8B"
	int64(__fastcall * Dvar_SetBoolByName_t)(const char* dvarName, bool value); //48 89 5C 24 ? 57 48 81 EC ? ? ? ? 0F B6 DA
	return reinterpret_cast<decltype(Dvar_SetBoolByName_t)>(JaysModz->baseModule + JaysModz->goffsets.Dvar_SetBoolByName)(dvarName, value);
}

uintptr_t Dvar_SetFloat_Internal(dvar_s* a1, float a2)
{
	//E8 ? ? ? ? 45 0F 2E C8 RESOLVE CALL
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, float a2)>(JaysModz->baseModule + JaysModz->goffsets.Dvar_SetFloat_Internal)(a1, a2);
}

uintptr_t Dvar_SetIntByName(const char* dvarname, int value)
{
	uintptr_t(__fastcall * Dvar_SetIntByName_t)(const char* dvarname, int value); //48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B DA 48 8B F9
	return reinterpret_cast<decltype(Dvar_SetIntByName_t)>(JaysModz->baseModule + JaysModz->goffsets.Dvar_SetIntByName)(dvarname, value);
}

void ProcessInformation()
{
	if (!JaysModz->msettings.b_ingame)
		return;
}

namespace sdk
{
	bool in_game()
	{
		return *(int*)(JaysModz->baseModule + JaysModz->goffsets.gamemode + 0x4) > 0;
	}
}