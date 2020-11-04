#pragma once

#include "structs.hpp"
#include "launcher/launcher.hpp"

#define SELECT_VALUE(sp, mp) (game::environment::is_sp() ? (sp) : (mp))

#define SERVER_CD_KEY "IW6x-CD-Key"

namespace game
{
	typedef void (*Sys_ShowConsole_t)();
	extern Sys_ShowConsole_t Sys_ShowConsole;

	typedef void (*Com_Frame_Try_Block_Function_t)();
	extern Com_Frame_Try_Block_Function_t Com_Frame_Try_Block_Function;

	typedef const char* (*Com_Parse_t)(char const**);
	extern Com_Parse_t Com_Parse;

	typedef void (*Com_Error_t)(int type, const char* message, ...);
	extern Com_Error_t Com_Error;

	typedef void (*Com_Quit_t)();
	extern Com_Quit_t Com_Quit;

	typedef CodPlayMode (*Com_GetCurrentCoDPlayMode_t)();
	extern Com_GetCurrentCoDPlayMode_t Com_GetCurrentCoDPlayMode;

	typedef void (*Com_SetSlowMotion_t)(const float, const float, const int);
	extern Com_SetSlowMotion_t Com_SetSlowMotion;

	typedef void (*Conbuf_AppendText_t)(const char* message);
	extern Conbuf_AppendText_t Conbuf_AppendText;

	typedef void (*Cbuf_AddText_t)(int localClientNum, const char* text);
	extern Cbuf_AddText_t Cbuf_AddText;

	typedef void (*Cbuf_ExecuteBufferInternal_t)(int localClientNum, int controllerIndex, const char* buffer,
	                                             void (*singleExecCmd)(int, int, const char*));
	extern Cbuf_ExecuteBufferInternal_t Cbuf_ExecuteBufferInternal;

	typedef bool (*CL_IsCgameInitialized_t)();
	extern CL_IsCgameInitialized_t CL_IsCgameInitialized;

	typedef void (*CG_GameMessage_t)(int localClientNum, const char* message);
	extern CG_GameMessage_t CG_GameMessage;

	typedef void (*Cmd_AddCommandInternal_t)(const char* cmdName, void (*function)(), cmd_function_s* allocedCmd);
	extern Cmd_AddCommandInternal_t Cmd_AddCommandInternal;

	typedef void (*Cmd_ExecuteSingleCommand_t)(int localClientNum, int controllerIndex, const char* text);
	extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

	typedef dvar_t* (*Dvar_FindVar_t)(const char* name);
	extern Dvar_FindVar_t Dvar_FindVar;

	typedef void (*Dvar_GetCombinedString_t)(char* buffer, int index);
	extern Dvar_GetCombinedString_t Dvar_GetCombinedString;

	typedef const char* (*Dvar_GetVariantStringWithDefault_t)(const char* dvarName, const char* defaultValue);
	extern Dvar_GetVariantStringWithDefault_t Dvar_GetVariantStringWithDefault;

	typedef dvar_t* (*Dvar_RegisterBool_t)(const char* dvarName, bool value, unsigned int flags,
	                                       const char* description);
	extern Dvar_RegisterBool_t Dvar_RegisterBool;

	typedef dvar_t* (*Dvar_RegisterEnum_t)(const char* dvarName, const char** valueList, int defaultIndex,
	                                       unsigned int flags, const char* description);
	extern Dvar_RegisterEnum_t Dvar_RegisterEnum;

	typedef dvar_t* (*Dvar_RegisterFloat_t)(const char* dvarName, float value, float min, float max,
	                                        unsigned int flags, const char* description);
	extern Dvar_RegisterFloat_t Dvar_RegisterFloat;

	typedef dvar_t* (*Dvar_RegisterInt_t)(const char* dvarName, int value, int min, int max, unsigned int flags,
	                                      const char* desc);
	extern Dvar_RegisterInt_t Dvar_RegisterInt;

	typedef dvar_t* (*Dvar_RegisterString_t)(const char* dvarName, const char* value, unsigned int flags,
	                                         const char* description);
	extern Dvar_RegisterString_t Dvar_RegisterString;

	typedef dvar_t* (*Dvar_RegisterVec2_t)(const char* dvarName, float x, float y, float min, float max,
	                                       unsigned int flags, const char* description);
	extern Dvar_RegisterVec2_t Dvar_RegisterVec2;

	typedef dvar_t* (*Dvar_RegisterVec4_t)(const char* dvarName, float x, float y, float z, float w, float min,
	                                       float max, unsigned int flags, const char* description);
	extern Dvar_RegisterVec4_t Dvar_RegisterVec4;

	typedef void (*Dvar_Reset_t)(dvar_t* dvar, DvarSetSource source);
	extern Dvar_Reset_t Dvar_Reset;

	typedef void (*Dvar_SetBool_t)(dvar_t* dvar, bool value);
	extern Dvar_SetBool_t Dvar_SetBool;

	typedef void (*Dvar_SetCommand_t)(const char* dvar, const char* buffer);
	extern Dvar_SetCommand_t Dvar_SetCommand;

	typedef void (*Dvar_SetString_t)(dvar_t* dvar, const char* string);
	extern Dvar_SetString_t Dvar_SetString;

	typedef void (*Dvar_Sort_t)();
	extern Dvar_Sort_t Dvar_Sort;

	typedef const char* (*Dvar_ValueToString_t)(dvar_t* dvar, dvar_value value);
	extern Dvar_ValueToString_t Dvar_ValueToString;

	typedef long long (*FS_ReadFile_t)(const char* qpath, char** buffer);
	extern FS_ReadFile_t FS_ReadFile;

	typedef void (*FS_FreeFile_t)(void* buffer);
	extern FS_FreeFile_t FS_FreeFile;

	typedef int (*G_RunFrame_t)(int server_time);
	extern G_RunFrame_t G_RunFrame;

	typedef char* (*I_CleanStr_t)(char* string);
	extern I_CleanStr_t I_CleanStr;

	typedef const char* (*Key_KeynumToString_t)(int, int, int);
	extern Key_KeynumToString_t Key_KeynumToString;

	typedef unsigned int (*Live_SyncOnlineDataFlags_t)(int);
	extern Live_SyncOnlineDataFlags_t Live_SyncOnlineDataFlags;

	typedef void (*LUI_OpenMenu_t)(int clientNum, const char* menu, int a3, int a4, unsigned int a5);
	extern LUI_OpenMenu_t LUI_OpenMenu;

	typedef bool (*Menu_IsMenuOpenAndVisible_t)(int clientNum, const char* menu);
	extern Menu_IsMenuOpenAndVisible_t Menu_IsMenuOpenAndVisible;

	typedef Material* (*Material_RegisterHandle_t)(const char* material);
	extern Material_RegisterHandle_t Material_RegisterHandle;

	typedef bool (*NET_StringToAdr_t)(const char* s, game::netadr_s* a);
	extern NET_StringToAdr_t NET_StringToAdr;

	typedef void (*R_AddCmdDrawStretchPic_t)(float x, float y, float width, float height, float s0, float t0,
	                                         float s1, float t1, float* color, Material* material);
	extern R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;

	typedef void (*R_AddCmdDrawText_t)(const char*, int, Font_s*, float, float, float, float, float, float*, int);
	extern R_AddCmdDrawText_t R_AddCmdDrawText;

	typedef void (*R_AddCmdDrawTextWithCursor_t)(const char*, int, Font_s*, float, float, float, float, float,
	                                             const float*, int, int, char);
	extern R_AddCmdDrawTextWithCursor_t R_AddCmdDrawTextWithCursor;

	typedef Font_s* (*R_RegisterFont_t)(const char* font);
	extern R_RegisterFont_t R_RegisterFont;

	typedef int (*R_TextWidth_t)(const char* text, int maxChars, Font_s* font);
	extern R_TextWidth_t R_TextWidth;

	typedef ScreenPlacement* (*ScrPlace_GetViewPlacement_t)();
	extern ScrPlace_GetViewPlacement_t ScrPlace_GetViewPlacement;

	typedef float(*Scr_GetFloat_t)(int index);
	extern Scr_GetFloat_t Scr_GetFloat;

	typedef int(*Scr_GetNumParam_t)();
	extern Scr_GetNumParam_t Scr_GetNumParam;

	typedef const char* (*SEH_StringEd_GetString_t)(const char*);
	extern SEH_StringEd_GetString_t SEH_StringEd_GetString;

	typedef void (*SV_GameSendServerCommand_t)(int, int, const char*);
	extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

	typedef bool (*SV_Loaded_t)();
	extern SV_Loaded_t SV_Loaded;

	typedef void (*SV_StartMap_t)(int localClientNum, const char* map, bool mapIsPreloaded);
	extern SV_StartMap_t SV_StartMap;

	typedef void (*SV_StartMapForParty_t)(int localClientNum, const char* map, bool mapIsPreloaded, bool migrate);
	extern SV_StartMapForParty_t SV_StartMapForParty;

	typedef mp::gentity_s* (*SV_AddBot_t)(const char*, unsigned int, unsigned int, unsigned int);
	extern SV_AddBot_t SV_AddBot;

	typedef bool (*SV_BotIsBot_t)(int clientNum);
	extern SV_BotIsBot_t SV_BotIsBot;

	typedef void (*SV_ExecuteClientCommand_t)(mp::client_t*, const char*, int);
	extern SV_ExecuteClientCommand_t SV_ExecuteClientCommand;

	typedef void (*SV_FastRestart_t)();
	extern SV_FastRestart_t SV_FastRestart;

	typedef const char* (*SV_GetGuid_t)(int clientNum);
	extern SV_GetGuid_t SV_GetGuid;

	typedef void (*SV_KickClientNum_t)(int clientNum, const char* reason);
	extern SV_KickClientNum_t SV_KickClientNum;

	typedef void (*SV_SetConfigstring_t)(int index, const char* string);
	extern SV_SetConfigstring_t SV_SetConfigstring;

	typedef void (*SV_SpawnTestClient_t)(mp::gentity_s*);
	extern SV_SpawnTestClient_t SV_SpawnTestClient;

	typedef bool (*Sys_IsDatabaseReady2_t)();
	extern Sys_IsDatabaseReady2_t Sys_IsDatabaseReady2;

	typedef int (*Sys_Milliseconds_t)();
	extern Sys_Milliseconds_t Sys_Milliseconds;

	//typedef bool (*Sys_SendPacket_t)(netsrc_t, int, void const*, netadr_s); // Actual
	typedef bool (*Sys_SendPacket_t)(int, void const*, const netadr_s*); // Compiler-optimized
	extern Sys_SendPacket_t Sys_SendPacket;

	typedef void (*SwitchToCoreMode_t)();
	extern SwitchToCoreMode_t SwitchToCoreMode;

	typedef void (*SwitchToAliensMode_t)();
	extern SwitchToAliensMode_t SwitchToAliensMode;

	typedef void (*SwitchToSquadVsSquadMode_t)();
	extern SwitchToSquadVsSquadMode_t SwitchToSquadVsSquadMode;

	typedef const char* (*UI_LocalizeMapname_t)(const char*);
	extern UI_LocalizeMapname_t UI_LocalizeMapname;
	extern UI_LocalizeMapname_t UI_LocalizeGametype;

	extern int* keyCatchers;

	extern CmdArgs* cmd_args;
	extern cmd_function_s** cmd_functions;

	extern int* dvarCount;
	extern dvar_t** sortedDvars;

	extern PlayerKeyState* playerKeys;

	extern SOCKET* query_socket;

	extern const char** command_whitelist;

	namespace sp
	{
		extern gentity_s* g_entities;
	}

	namespace mp
	{
		extern cg_s* cgArray;

		extern gentity_s* g_entities;

		extern int* svs_numclients;
		extern client_t* svs_clients;

		extern std::uint32_t* sv_serverId_value;

		extern int* gameTime;
		extern int* serverTime;
	}

	int Cmd_Argc();
	const char* Cmd_Argv(int index);

	int SV_Cmd_Argc();
	const char* SV_Cmd_Argv(int index);

	namespace environment
	{
		launcher::mode get_mode();

		bool is_mp();
		bool is_sp();
		bool is_dedi();

		void set_mode(launcher::mode mode);
		void initialize();
	}
}
