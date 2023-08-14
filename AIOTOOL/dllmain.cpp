#include "dllmain.h"
#include <sys/stat.h>

HANDLE hMainThread = NULL;

float crosshair_col[3] = { 255.f / 255.f, 255.f , 255.f };

ImColor crosshaircolor = ImColor(0.f, 0.f, 255.f, 255.f);

bool is_key_down(int vk_key)
{
	return ((GetAsyncKeyState(vk_key) & 0x8000) ? 1 : 0);
}

void draw_line(const ImVec2& from, const ImVec2& to, C_Color color, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddLine(from, to, color.GetU32(), thickness);
}

//#ifndef  NDEBUG
void Log_(const char* fmt, ...) {
	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	std::ofstream logfile(xorstr_("C:\\aiotool\\debug\\aio_debuglog.logs"), std::ios::app);
	if (logfile.is_open() && text)	logfile << text << std::endl;
	logfile.close();
}
//#endif
bool IsPathExist(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}

uint64_t BASEIMAGE = reinterpret_cast<uint64_t>(GetModuleHandleA(NULL));

void init()
{
	JaysModz = new global_vars();
	JaysModz->msettings.screenX = GetSystemMetrics(SM_CXSCREEN);
	JaysModz->msettings.screenY = GetSystemMetrics(SM_CYSCREEN);
	JaysModz->procID = utility::GetProcId(L"ModernWarfare.exe");
	JaysModz->hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, JaysModz->procID);
	JaysModz->baseModule = (QWORD)(iat(GetModuleHandleA).get()("ModernWarfare.exe"));
	JaysModz->hWind = process::get_process_window();

}

__declspec(dllexport)HRESULT present_hk(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!pSwapChain)
		return ori_present(pSwapChain, SyncInterval, Flags);
	if (d3d12::pCommandQueue == nullptr)
	{
		ori_present(pSwapChain, SyncInterval, Flags);
	}

	DXGI_SWAP_CHAIN_DESC sdesc;
	pSwapChain->GetDesc(&sdesc);
	if (sdesc.OutputWindow == GetForegroundWindow())
	{
		Main = imgui::start(
			reinterpret_cast<IDXGISwapChain3*>(pSwapChain),
			reinterpret_cast<ID3D12CommandQueue*>((d3d12::pCommandQueue)), nullptr, 16.0f);

		imgui::imgui_frame_header();

		if (GetAsyncKeyState(VK_END) & 1)
			kiero::shutdown();

		if (GetAsyncKeyState(VK_HOME) & 1)
			JaysModz->msettings.b_menuEnable = !JaysModz->msettings.b_menuEnable;

		if (JaysModz->msettings.b_menuEnable)
		{
			ImGui::GetIO().MouseDrawCursor;
			menu->MENUSHOW();
		}

		/*if (JaysModz->msettings.chrosshair)
		{
			constexpr long crosshair_size = 10.0f;
			ImVec2 origin;
			origin.x = screenX / static_cast<float>(2);
			origin.y = screenY / static_cast<float>(2);
			draw_line(ImVec2((origin.x), (origin.y) - crosshair_size), ImVec2((origin.x), (origin.y) + crosshair_size), JaysModz->msettings.crosshair_color.color(), 1.5f);
			draw_line(ImVec2((origin.x) - crosshair_size, (origin.y)), ImVec2((origin.x) + crosshair_size, (origin.y)), JaysModz->msettings.crosshair_color.color(), 1.5f);
		}*/

		//if (JaysModz->msettings.b_dynamic3p)
		//{
		//	/*dvar_set2("NOSLRNTRKL", 1);*/
		//	if (is_key_down(VK_RBUTTON) || is_key_down(VK_GAMEPAD_LEFT_TRIGGER))
		//	{
		//		dvar_set2("NOSLRNTRKL", 0);
		//	}
		//	else
		//	{
		//		dvar_set2("NOSLRNTRKL", 1);
		//	}
		//}
	
		imgui::imgui_no_border();
		g_game::init(Main);
		imgui::imgui_frame_end();
	}
	return ori_present(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI  initthread(HMODULE hModule)
{
	hMainThread = GetCurrentThread();

	init();

	if (JaysModz->procID)
	{
	//    JaysModz->goffsets.unlock_offsets = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x500000, 0x1F0000, xorstr_("\x33\xFF\x48\x8D\x15\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x8D\x0D"), xorstr_("xxxxx????xxx????xxx")) - JaysModz->baseModule;
		JaysModz->goffsets.Dvar_FindVarByName = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x5A00000, 0x2000000, xorstr_("\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x75\x04\x33"), xorstr_("x????xxxxxxxxx"), 0, 4, 1);
		JaysModz->goffsets.Dvar_SetBoolInternal = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x2000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x4C\x8D\x35\x00\x00\x00\x00\x74\x43\x33\xD2\xF7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x76\x2E"), xorstr_("x????xx?????xxx????xxxxxx????????xx"), 1, 5, 0);
		JaysModz->goffsets.Dvar_SetInt_Internal = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x3000000, 0x1F00000, xorstr_("\x40\x53\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x84\x24\x00\x00\x00\x00\x0F\xB6\x41\x09\x48\x8B\xD9"), xorstr_("xxxxx????xxx????xxxxxxx????xxxxxxx")) - JaysModz->baseModule;
		JaysModz->goffsets.Dvar_SetBoolByName = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x3000000, 0x1F00000, xorstr_("\x48\x89\x5C\x24\x00\x57\x48\x81\xEC\x00\x00\x00\x00\x0F\xB6\xDA"), xorstr_("xxxx?xxxx????xxx")) - JaysModz->baseModule;
		JaysModz->goffsets.Dvar_SetFloat_Internal = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x5900000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x45\x0F\x2E\xC8"), xorstr_("x????xxxx"), 1, 5, 0);
		JaysModz->goffsets.camoAddr = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x2000000, 0x1F00000, xorstr_("\x4C\x8B\x00\x00\x00\x00\x00\x4C\x8B\x00\x00\x00\x00\x00\x4D\x85\x00\x74\x00\x49\xB9"), xorstr_("xx?????xx?????xx?x?xx"),3,7,0);
		JaysModz->goffsets.camoAddr += 0x28;
		JaysModz->goffsets.ddl_loadasset = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x3300000, 0x1F00000, xorstr_("\xe8\x00\x00\x00\x00\x48\x8b\x00\x4c\x8d\x4c\x24\x00\x33\xc0\x48\x8d\x0d\x00\x00\x00\x00"), xorstr_("x????xx?xxxx?xxxxx????"), 1, 5, 0);
		JaysModz->goffsets.ddl_getrootstate = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x2300000, 0x1F00000, xorstr_("\xe8\x00\x00\x00\x00\x8b\x0d\x00\x00\x00\x00\x0f\x10\x00"), xorstr_("x????xx????xx?"), 1, 5, 0);
		JaysModz->goffsets.ddl_getdllbuffer = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x4000000, 0x1F00000, xorstr_("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x48\x8B\xE9\x49\x63\xF8\x41\x8B\xC9\x48\x63\xF2\x41\x8B\xD9\xE8\x00\x00\x00\x00"), xorstr_("xxxx?xxxx?xxxx?xxxxxxxxxxxxxxxxxxxxx????")) - JaysModz->baseModule;	;
		JaysModz->goffsets.ddl_movetoname = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x4000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x84\xC0\x74\x22\x48\x8D\x54\x24\x40"), xorstr_("x????xxxxxxxxx"), 1, 5, 0);;
	    JaysModz->goffsets.ddl_movetopath = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x6500000, 0xF00000, "\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x41\x56\x48\x83\xEC\x20\x4D\x8B\xF1\x48\x8B\xFA\x48\x85\xC9", "xxxx?xxxx?xxxxxxxxxxxxxxx") - JaysModz->baseModule;
		JaysModz->goffsets.ddl_setint = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x4000000, 0x1F00000, xorstr_("\x44\x8B\xC0\x48\x8D\x55\xB7\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00"), xorstr_("xxxxxxxxxxx?x????"), 1, 5, 12);
		JaysModz->goffsets.ddl_setstring = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x6800000, 0xF00000, "\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x49\x8B\xF0\x48\x8B\xFA\x48\x8B\xD9\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\x48\x8B\x42\x10\x48\x85\xC0\x0F\x84\x00\x00\x00\x00", "xxxx?xxxx?xxxxxxxxxxxxxxxxxxx????xxxxxxxxx????") - JaysModz->baseModule;
		JaysModz->goffsets.ddl_getint = utility::PatternScanExCustom(JaysModz->hProc, JaysModz->baseModule + 0x6500000, 0xF00000, "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xFA\x48\x8B\xD9\x48\x85\xD2\x74\x7F\x48\x8B\x42\x10\x48\x85\xC0\x74\x76", "xxxx?xxxxxxxxxxxxxxxxxxxxxxxxx", 2) - JaysModz->baseModule;
		JaysModz->goffsets.a_parse = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x02D00000, 0xF00000, "\x40\x55\x56\x41\x54\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x45\x33\xF6\x4D\x8B\xF9\x45\x89\x31", "xxxxxxxxxxxx????xxx????xxxxxxx?xxxxxxxxx") - JaysModz->baseModule;
		JaysModz->goffsets.clantag_offset = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x03C00000, 0xF00000, "\x40\x53\x48\x83\xEC\x30\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x4C\x8B\xCA\x41\xB8\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\x8B\xD9", "xxxxxxxxx????xxxxxxx?xxxxx????xx????xx") - JaysModz->baseModule;
		JaysModz->goffsets.ddl_setenum = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x06800000, 0xF00000, "\x48\x89\x5C\x24\x0000\x57\x48\x83\xEC\x20\x48\x8B\xFA\x48\x8B\xD9\x33\xD2\x49\x8B\xC8\xE8", "xxxx?xxxxxxxxxxxxxxxxx") - JaysModz->baseModule;
		JaysModz->goffsets.chamOffset = utility::PatternScanEx(JaysModz->hProc, JaysModz->baseModule + 0x05900000, 0xF00000, xorstr_("\x48\x83\xEC\x58\x83\x3D\x00\x00\x00\x00\x00\xF3\x0F\x10\x84\x24\x00\x00\x00\x00\x74\x34\x33\xC0\x89\x44\x24\x40"), xorstr_("xxxxxx?????xxxxx????xxxxxxxx")) - JaysModz->baseModule;
		JaysModz->goffsets.playerCountOffset = utility::FindOffset(JaysModz->hProc, JaysModz->baseModule + 0x02000000, 0xF00000, xorstr_("\x83\x3d\x00\x00\x00\x00\x00\x41\xbe"), "xx?????xx", 2, 6, 0) + 1;
		JaysModz->goffsets.inGameOffset = JaysModz->goffsets.playerCountOffset + 0x04;

		if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success)
		{
			kiero::bind(54, (void**)&oExecuteCommandListsD3D12, imgui::hookExecuteCommandListsD3D12);
			kiero::bind(140, (void**)&ori_present, present_hk);
		
		}
	}
	else
	{
		return 0;
	}


	return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		initthread(module);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
	return TRUE;
}