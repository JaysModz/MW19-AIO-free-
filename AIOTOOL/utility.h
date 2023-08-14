#pragma once
#include "framework.h"

namespace utility
{
	DWORD GetProcId(const wchar_t* procName);
	HMODULE GetModuleHandleSafe(const wchar_t* pszModuleName);
	void Read(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void Write(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	uintptr_t PointerChain(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	void Patch(BYTE* dst, BYTE* src, unsigned size);
	void Nop(BYTE* dst, unsigned int size);
	uintptr_t PatternScanEx(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask);
	uintptr_t FindOffset(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask, uintptr_t base_offset, uintptr_t pre_base_offset, uintptr_t rindex, bool addRip = true);
	DWORD  FindPattern(uintptr_t start, uintptr_t size, const char* pattern, const char* mask);
	uintptr_t PatternScanExCustom(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask, int index);
	void PatchBytes(BYTE* destination, BYTE* source, size_t size);
}