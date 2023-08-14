#pragma once
#include "framework.h"
#include "globals.h"
#include "mem.h"


extern HMODULE m_hModule;

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
#define WND_SIZEX GetSystemMetrics(SM_CXSCREEN) 
#define WND_SIZEY GetSystemMetrics(SM_CYSCREEN) 
__int64 Com_DDL_LoadAsset(__int64 file);
__int64 DDL_GetRootState(__int64 state, __int64 file);
bool CL_PlayerData_GetDDLBuffer(__int64 context, int controllerindex, int stats_source, unsigned int statsgroup);
bool ParseShit(const char* a, const char** b, const int c, int* d);
char DDL_MoveToPath(__int64* fromState, __int64* toState, int depth, const char** path);
__int64 DDL_MoveToName(__int64 fstate, __int64 tstate, __int64 path);
char DDL_SetInt(__int64 fstate, __int64 context, unsigned int value);
char DDL_SetInt2(__int64* fstate, __int64* context, int value);
int DDL_GetInt(__int64* fstate, __int64* context);
char DDL_SetString(__int64 fstate, __int64 context, const char* value);
template <typename T>
bool IsValidPtr(PVOID ptr)
{
	if (is_bad_ptr(ptr))return false;
	else
		return true;

}

namespace process
{
	extern HWND hwnd;
	BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam);
	HWND get_process_window();
	HWND get_process_window(DWORD procID);
}

namespace EngineFeatures
{
	void EnableFeatures();
}

namespace g_game
{
	void init(ImFont* font);
}

/* 430 */
struct unnamed_type_enumeration
{
	int stringCount;
	const char* strings;
};

/* 431 */
struct unnamed_type_integer
{
	int min;
	int max;
};

/* 432 */
struct unnamed_type_integer64
{
	__int64 min;
	__int64 max;
};

/* 433 */
struct unnamed_type_unsignedInt64
{
	unsigned __int64 min;
	unsigned __int64 max;
};

/* 434 */
struct unnamed_type_value
{
	float min;
	float max;
	float devguiStep;
};

/* 435 */
struct unnamed_type_vector
{
	float min;
	float max;
	float devguiStep;
};

/* 436 */
union DvarLimits
{
	unnamed_type_enumeration enumeration;
	unnamed_type_integer integer;
	unnamed_type_integer64 integer64;
	unnamed_type_unsignedInt64 unsignedInt64;
	unnamed_type_value value;
	unnamed_type_vector vector;
};

union DvarValue
{
	bool enabled; //0x0000
	int32_t integer; //0x0000
	uint32_t unsignedInt; //0x0000
	float value; //0x0000
	//Vector4 vector; //0x0000
	const char* string; //0x0000
	unsigned __int8 color[4]; //0x0000
	uint64_t unsignedInt64; //0x0000
	int64_t integer64; //0x0000
};

typedef enum DvarType : uint8_t
{
	DVAR_TYPE_BOOL = 0x0,
	DVAR_TYPE_FLOAT = 0x1,
	DVAR_TYPE_FLOAT_2 = 0x2,
	DVAR_TYPE_FLOAT_3 = 0x3,
	DVAR_TYPE_FLOAT_4 = 0x4,
	DVAR_TYPE_INT = 0x5,
	DVAR_TYPE_INT64 = 0x6,
	DVAR_TYPE_UINT64 = 0x7,
	DVAR_TYPE_ENUM = 0x8,
	DVAR_TYPE_STRING = 0x9,
	DVAR_TYPE_COLOR = 0xA,
	DVAR_TYPE_FLOAT_3_COLOR = 0xB,
	DVAR_TYPE_COUNT = 0xC,
} DvarType;

struct dvar_s
{
	char name[4]; //0x0
	uint32_t flags; //0x4
	BYTE level[1]; //0x8
	DvarType type; //0x9
	bool modified; //0xA
	uint32_t checksum; //0xC
	char* description; //0x10
	char pad2[16]; //0x18
	unsigned __int16 hashNext; //0x28
	DvarValue current; //0x30
	DvarValue latched; //0x40
	DvarValue reset; //0x50
	DvarLimits domain; //0x60
	//BbConstUsageFlags BbConstUsageFlags;
};

void unlock();
void CL_PlayerData_SetCustomClanTag(const char* clanTag);
dvar_s* Dvar_FindVarByName(const char* dvarName);
uintptr_t Dvar_SetBoolByName(const char* dvarName, bool value);
uintptr_t Dvar_SetFloat_Internal(dvar_s* a1, float a2);
uintptr_t Dvar_SetInt_Internal(dvar_s* a1, unsigned int a2);
uintptr_t Dvar_SetBool_Internal(dvar_s* a1, bool a2);

inline const char* dvartype(const char* dvarname)
{
	dvar_s* varbyname = Dvar_FindVarByName(dvarname);
	if (varbyname)
	{
		switch (varbyname->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{
			return "DVAR_TYPE_BOOL";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			return "DVAR_TYPE_FLOAT";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_2: //vec2
		{
			return "DVAR_TYPE_FLOAT_2";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3: //vec3
		{
			return "DVAR_TYPE_FLOAT_3";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_4: //vec4
		{
			return "DVAR_TYPE_FLOAT_4";
			break;
		}
		case DvarType::DVAR_TYPE_INT:
		{
			return "DVAR_TYPE_INT";
			break;
		}
		case DvarType::DVAR_TYPE_INT64:
		{
			return "DVAR_TYPE_INT64";
			break;
		}
		case DvarType::DVAR_TYPE_UINT64:
		{
			return "DVAR_TYPE_UINT64";
			break;
		}
		case DvarType::DVAR_TYPE_ENUM:
		{
			return "DVAR_TYPE_ENUM";
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			return "DVAR_TYPE_STRING";
			break;
		}
		case DvarType::DVAR_TYPE_COLOR:
		{
			return "DVAR_TYPE_COLOR";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3_COLOR:
		{
			return "DVAR_TYPE_FLOAT_3_COLOR";
			break;
		}
		//case DvarType::DVAR_TYPE_COUNT:
		//	return std::to_string(varbyname->current.);
		//	break;
		default:
			return "[NA]";
			break;
		}
	}
}
struct DDLMember {
	const char* name;
	int index;
	int bitSize;
	int limitSize;
	int offset;
	int type;
	int externalIndex;
	unsigned int rangeLimit;
	bool isArray;
	int arraySize;
	int enumIndex;
};

struct DDLHash {
	unsigned int hash;
	int index;
};

struct DDLHashTable {
	DDLHash* list;
	int count;
	int max;
};

struct DDLStruct {
	const char* name;
	int bitSize;
	int memberCount;
	DDLMember* members;
	DDLHashTable hashTableUpper;
	DDLHashTable hashTableLower;
};

struct DDLEnum {
	const char* name;
	int memberCount;
	const char** members;
	DDLHashTable hashTable;
};

struct DDLDef {
	char* name;
	unsigned __int16 version;
	unsigned __int64 guidSeed;
	unsigned __int64 guid;
	int bitSize;
	int byteSize;
	DDLStruct* structList;
	int structCount;
	DDLEnum* enumList;
	int enumCount;
	DDLDef* next;
	int headerBitSize;
	int headerByteSize;
	bool paddingUsed;
	bool minimalHeader;
};

struct DDLState {
	bool isValid;
	int offset;
	int arrayIndex;
	DDLMember* member;
	const DDLDef* ddlDef;
};

struct DDLContext {
	void* buff;
	int len;
	const DDLDef* def;
	void* userData;
	bool obfuscated;
	unsigned int randomInt;
};
static uintptr_t AVAL = NULL;
[[nodiscard]] static BYTE* currentDvarVal(const char* cmnd, uintptr_t& addr = AVAL)
{
	//BYTE* buff = new BYTE[1024];
	//std::unique_ptr < BYTE[] > buff(new BYTE[256]);
	auto buff = std::make_unique<BYTE[]>(256);

	std::string result = "(null)";
	dvar_s* varbyname = Dvar_FindVarByName(cmnd);
	if (varbyname)
	{
		addr = (uintptr_t)varbyname;
		switch (varbyname->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{

			result = std::to_string(varbyname->current.enabled);
			//strcpy(buff.get(), result.c_str());
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			result = std::to_string(varbyname->current.value);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		
		case DvarType::DVAR_TYPE_INT:
		{
			result = std::to_string(varbyname->current.integer);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_INT64:
		{
			result = std::to_string(varbyname->current.integer64);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_UINT64:
		{
			result = std::to_string(varbyname->current.unsignedInt64);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_ENUM:
		{
			result = std::to_string(varbyname->current.integer);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			result = varbyname->current.string;
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_COLOR:
		{
			result =
				" r: " + std::to_string(varbyname->current.color[0]) +
				" g: " + std::to_string(varbyname->current.color[1]) +
				" b: " + std::to_string(varbyname->current.color[2]) +
				" a: " + std::to_string(varbyname->current.color[3]);

			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3_COLOR:
		{
			result =
				" r: " + std::to_string(varbyname->current.color[0]) +
				" g: " + std::to_string(varbyname->current.color[1]) +
				" b: " + std::to_string(varbyname->current.color[2]);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		default:
			break;
		}
	}
	addr = NULL;
	//delete[] buff;
	return (BYTE*)result.c_str();
}

template<typename T> inline void dvar_set(const char* dvarName, T value)
{
	dvar_s* dvar = Dvar_FindVarByName(dvarName);
	if (dvar)
	{
		if (dvar->flags > 0)
		{
			dvar->flags = 0;
		}
		switch (dvar->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{
			return Dvar_SetBoolByName(dvarName, value);
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			return Dvar_SetFloat_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_2: //vec2
		{
			//Dvar_SetVec2_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3: //vec3
		{
			//Dvar_SetVec3_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_4: //vec4
		{
			//Dvar_SetVec4_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_INT:
		{
			//Dvar_SetInt_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_INT64:
		{
			//Dvar_SetInt64_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_UINT64:
		{
			//Dvar_SetUInt64_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_ENUM:
		{
			return;
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			return;
			break;
		}
		case DvarType::DVAR_TYPE_COLOR:
		{
			return;
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3_COLOR:
		{
			return;
			break;
		}
		//case DvarType::DVAR_TYPE_COUNT:
		//	return std::to_string(varbyname->current.);
		//	break;
		default:
			return;
			break;
		}
	}
}

inline void dvarFloat(const char* dvarname, float val)
{
	auto DVARFLT_cg_fovScale = Dvar_FindVarByName(dvarname);
	if (DVARFLT_cg_fovScale)
	{
		Dvar_SetFloat_Internal(DVARFLT_cg_fovScale, val);
	}
}

inline uint32_t dvarflag(const char* dvarname)
{
	auto DVARFLT_cg_fovScale = Dvar_FindVarByName(dvarname);
	if (DVARFLT_cg_fovScale)
	{
		return DVARFLT_cg_fovScale->flags;
	}
	return NULL;
}

static void dvar_setBool(const char* dvarname, bool val)
{
	dvar_s* tpv = Dvar_FindVarByName(dvarname);
	if (tpv)
	{
		if (tpv->flags > 0)
		{
			tpv->flags = 0;
		}
		Dvar_SetBoolByName(dvarname, val);
	}
}

__int64 Cmd_ExecuteSingleCommand(int clientnum, __int64 command);

template<typename T> inline void dvar_set2(const char* dvarName, T value)
{
	dvar_s* dvar = Dvar_FindVarByName(dvarName);
	if (dvar)
	{
		if (dvar->flags > 0)
		{
			dvar->flags = 0;
		}
		switch (dvar->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{
			Dvar_SetBool_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			Dvar_SetFloat_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_INT:
		{
			Dvar_SetInt_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			break;
		}
		default:
			break;
		}
	}
}