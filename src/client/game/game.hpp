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

	typedef void (*Conbuf_AppendText_t)(const char* message);
	extern Conbuf_AppendText_t Conbuf_AppendText;

	typedef void (*Com_Error_t)(int type, const char* message, ...);
	extern Com_Error_t Com_Error;

	typedef void (*Cbuf_AddText_t)(int localClientNum, const char* text);
	extern Cbuf_AddText_t Cbuf_AddText;

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

	typedef void (*Dvar_Sort_t)();
	extern Dvar_Sort_t Dvar_Sort;

	typedef const char* (*Dvar_ValueToString_t)(dvar_t* dvar, dvar_value value);
	extern Dvar_ValueToString_t Dvar_ValueToString;

	typedef int (*G_RunFrame_t)(int server_time);
	extern G_RunFrame_t G_RunFrame;

	typedef void (*LUI_OpenMenu_t)(int clientNum, const char* menu, int a3, int a4, unsigned int a5);
	extern LUI_OpenMenu_t LUI_OpenMenu;

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

	typedef const char* (*SEH_StringEd_GetString_t)(const char*);
	extern SEH_StringEd_GetString_t SEH_StringEd_GetString;

	typedef void (*SV_GameSendServerCommand_t)(int, int, const char*);
	extern SV_GameSendServerCommand_t SV_GameSendServerCommand;
	typedef bool (*SV_Loaded_t)();
	extern SV_Loaded_t SV_Loaded;

	typedef int (*Sys_Milliseconds_t)();
	extern Sys_Milliseconds_t Sys_Milliseconds;

	//typedef bool (*Sys_SendPacket_t)(netsrc_t, int, void const*, netadr_s); // Actual
	typedef bool (*Sys_SendPacket_t)(int, void const*, const netadr_s*); // Compiler-optimized
	extern Sys_SendPacket_t Sys_SendPacket;

	extern int* keyCatchers;

	extern CmdArgs* cmd_args;
	extern cmd_function_s** cmd_functions;

	extern int* dvarCount;
	extern dvar_t** sortedDvars;

	extern PlayerKeyState* playerKeys;

	extern SOCKET* query_socket;

	namespace sp
	{
		extern gentity_s* g_entities;
	}

	namespace mp
	{
		extern cg_s* cgArray;

		extern gentity_s* g_entities;
	}

	int Cmd_Argc();
	const char* Cmd_Argv(int index);

	int SV_Cmd_Argc();
	const char* SV_Cmd_Argv(int index);

	namespace environment
	{
		bool is_mp();
		bool is_sp();
		bool is_dedi();

		void initialize(launcher::mode mode);
	}
}
