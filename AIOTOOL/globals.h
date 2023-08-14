#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include "framework.h"
#include "color.h"

typedef struct _settings
{
	bool b_menuEnable = true;
	bool b_debugEnable = true;
	bool b_map = false;
	bool open = true;
	bool b_fov = false;
	bool b_heart = false;
	bool b_unlock = false;
	bool b_tut = false;
	bool b_fps = false;
	bool b_priv = false;
	bool b_no_flashbang = false;
	bool b_custom_clantag = false;
	bool b_brightmax = false;
	float f_fov = 1.2f;
	float f_map = 1.0f;
	bool b_Thirdperson = false;
	bool b_sThirdperson = false;
	bool b_sprint = false;
	bool b_test = false;
	bool b_shield = false;
	bool b_no_fog = false;
	bool b_gun = false;
	bool b_no_stun = false;
	bool b_ingame = false;
	bool b_owner = false;
	float testing = 0.1f;
	bool b_testing = false;
	bool b_fuckview = false;
	int i_score = 1; //1 ~ 5555555555
	int i_timeplayed = 1;
	int i_games = 1; //1 ~ 5555555555
	int i_wins = 1; //1 ~ 5555555555
	int i_kills = 1; //1 ~ 5555555555
	int i_deaths = 1; //1 ~ 5555555555
	int i_downs = 1; //1 ~ 5555555555;
	int i_top5 = 1; //1 ~ 5555555555
	int i_top10 = 1; //1 ~ 5555555555
	int i_top25 = 1; //1 ~ 5555555555
	bool b_name = false;
	bool b_no_hud = false;
	bool b_crosshair = false;
	bool chrosshair = false;
	bool b_dynamic3p = false;
	bool b_recoil = false;
	//
	bool bMisc1 = false;
	bool bMisc2 = false;
	bool bMisc3 = false;
	bool bMisc4 = false;
	bool bMisc5 = false;
	bool bMisc6 = false;
	bool bMisc7 = false;
	bool bMisc8 = false;
	bool bMisc9 = false;
	bool bMisc10 = false;
	bool bMiscPage = false;
	bool bMiscPage2 = false;
	bool bMiscMPWZClassName = false;
	bool bMiscMPWZCamoClass = false;
	bool bMiscMPWZDG = false;
	bool bMiscMPWZOS = false;
	bool bMiscRebirthSelected = false;
	bool bMiscBRSelected = false;
	bool bMiscBRPage2 = false;
	bool bSetCamo = false;
	bool bSetCamoAll = false;
	bool bSetPresetClanTag = false;
	bool bSetCustomClanTag = false;
	bool bSetOPMP1 = false;
	bool bSetOPMP2 = false;
	bool bSetOPWZ = false;
	bool bSetDoubleGun = false;
	bool bSetDoubleGunAll = false;
	bool bSetClassName = false;
	bool bSetClassNameAll = false;
	//
	char cClassEditorBuf[128] = " Enter Class Name";
	char cCustomClanTagBuf[128] = " Custom Clan Tag";
	std::string sPresetClanTag = "";
	std::string sCustomClanTag = "";
	std::string sClassName = "";
	//
	int iGameMode = 0;
	int iGameMode2 = 0;
	int iGameMode3 = 0;
	int iGameMode4 = 0;
	int iLoadoutSelection = 0;
	int iOPSelection = 0;
	int iCamoLoadoutSelection = 0;
	int iWeaponSelection = 0;
	int iCamoSelection = 0;
	int iClassNameSelection = 0;
	//
	bool bRebirthWins = false;
	bool bRebirthTop5 = false;
	bool bRebirthKills = false;
	bool bRebirthDeaths = false;
	int iRebirthWins = 1;
	int iRebirthTop5 = 1;
	int iRebirthKills = 1;
	int iRebirthDeaths = 1;
	//
	bool bBRScore = false;
	bool bBRGamesPlayed = false;
	bool bBRTimePlayed = false;
	bool bBRWins = false;
	bool bBRTop5 = false;
	bool bBRKills = false;
	bool bBRDeaths = false;
	bool bBRDowns = false;
	int iBRScore = 1;
	int iBRGamesPlayed = 1;
	int iBRTimePlayed = 1;
	int iBRWins = 1;
	int iBRTop5 = 1;
	int iBRKills = 1;
	int iBRDeaths = 1;
	int iBRDowns = 1;
	//
	int iFovValue = 1;
	int iMiniMapValue = 1;

	float fCrosshair_color[4] = { 1, 1, 1, 1 };
	ImColor crosshair_color = ImColor(fCrosshair_color[0], fCrosshair_color[1], fCrosshair_color[2]);
	//utils::color_var crosshair_color = utils::color_var(C_Color(255, 255, 255));
	utils::color_var menu_color = utils::color_var(C_Color(255, 255, 255));
	//
	int screenX = NULL;
	int screenY = NULL;

	bool visibleOutlines = false;
	bool chams = false;
	bool chamHooked = false;
	bool notVisibleOutlines = false;
	int rendertype = 0;
	bool chamFill = false;
	int lineWidthNum = 2;
	int chamColorRGB;
	int playerColor;
	int lootColor;
	bool initFont = false;
	bool lootChams = false;
	bool rgbChams = false;

} settings;


typedef struct _offsets
{
	uintptr_t gamemode;
	uintptr_t camoAddr; //= 0x1A7C7918 + 0x28;
	uintptr_t mwcamoAddr;
	uintptr_t perkAddr1;
	uintptr_t perkAddr2;
	uintptr_t perkAddr3;
	uintptr_t cwcamoAddr;
	uintptr_t vgcamoAddr;
	uintptr_t clantag_offset;
	uintptr_t a_parse;
	uintptr_t unlock_offsets;
	uintptr_t Dvar_FindVarByName;
	uintptr_t Dvar_SetBoolInternal;
	uintptr_t Dvar_SetBoolByName;
	uintptr_t Dvar_SetFloat_Internal;
	uintptr_t Dvar_RegisterFloat;
	uintptr_t Dvar_SetInt_Internal;
	uintptr_t Dvar_SetIntByName;
	//stats
	uintptr_t ddl_loadasset;
	uintptr_t ddl_getrootstate;
	uintptr_t ddl_parse = 0x0;
	uintptr_t ddl_getdllbuffer;
	uintptr_t ddl_movetoname;
	uintptr_t ddl_movetopath;
	uintptr_t ddl_setint;
	uintptr_t ddl_setenum;
	uintptr_t ddl_getint;
	uintptr_t ddl_setstring;
	uintptr_t Logon_Status;

	uintptr_t chamOffset;
	uintptr_t playerCountOffset;
	uintptr_t inGameOffset;
} offsets;

typedef struct Cached
{
	uintptr_t local_ptr;
	uintptr_t player_ptr;
	uint64_t cached_character_ptr;
	uint64_t cached_base_ptr;
	uint64_t cached_entity_ptr;
	uint64_t inputptr;
	uint64_t entity_ptr;
	QWORD current_visible_offset;
	QWORD cached_visible_base;
	QWORD last_visible_offset;
	int local_team_id;
	int player_team_id;
	uint32_t local_index;
	bool b_is_localalive;
	bool b_is_playeralive;

} Cached;

typedef struct _global_vars
{
	DWORD procID;
	HWND hWind;
	HANDLE hProc;
	HWND hGame = NULL;
	uintptr_t baseModule;
	uint64_t moduleBase;
	offsets goffsets;
	settings msettings;
	Cached gCached;

} global_vars;

extern global_vars* JaysModz;

#endif // !GLOBAL_H

