#pragma once



#define _PTR_MAX_VALUE ((PVOID)0x000F000000000000)
#define BYTEn(x, n)   (*((BYTE*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)

//auto padding
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define is_valid_ptr(p) ((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))

#define Exit() 0
#define QWORD unsigned __int64

//#ifndef  NDEBUG
#define LOGS(fmt, ...) Log_(xorstr_(fmt), ##__VA_ARGS__)

#define LOGS_ADDR(var_name)										\
		LOGS(#var_name ": 0x%llX (0x%llx)", var_name, var_name > JaysModz->baseModule - 0x10000 ? var_name -  JaysModz->baseModule  : 0);
extern void Log_(const char* fmt, ...);
//#endif NDEBUG


extern void Log_(const char* fmt, ...);

#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <timeapi.h>
#include <unordered_map>
#include <map>
#include <timeapi.h>
#include <sysinfoapi.h>
#include <filesystem>
#include <functional>
#include <vector>

#include "xorstr.hpp"
#include "lazyimporter.h"
#include "defs.h"

#include "includes/imgui/imgui.h"
#include "includes/imgui/imgui_internal.h"

#include "includes/imgui/imgui_impl_win32.h"
#include "includes/imgui/imgui_impl_dx12.h"
#include <dxgi1_4.h>

#include "includes/kiero/kiero.h"

#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

#include "includes/minhook/MinHook.h"
#pragma comment(lib, "minhook.lib")