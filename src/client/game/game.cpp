#include <std_include.hpp>
#include "game.hpp"

namespace game
{
	Sys_ShowConsole_t Sys_ShowConsole;

	Com_Frame_Try_Block_Function_t Com_Frame_Try_Block_Function;
	Com_Parse_t Com_Parse;
	Com_Error_t Com_Error;
	Com_Quit_t Com_Quit;
	Com_GetCurrentCoDPlayMode_t Com_GetCurrentCoDPlayMode;
	Com_SetSlowMotion_t Com_SetSlowMotion;

	Conbuf_AppendText_t Conbuf_AppendText;

	Cbuf_AddText_t Cbuf_AddText;
	Cbuf_ExecuteBufferInternal_t Cbuf_ExecuteBufferInternal;

	CG_GameMessage_t CG_GameMessage;

	CL_IsCgameInitialized_t CL_IsCgameInitialized;

	Cmd_AddCommandInternal_t Cmd_AddCommandInternal;
	Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

	Dvar_FindVar_t Dvar_FindVar;
	Dvar_GetCombinedString_t Dvar_GetCombinedString;
	Dvar_GetVariantStringWithDefault_t Dvar_GetVariantStringWithDefault;
	Dvar_RegisterBool_t Dvar_RegisterBool;
	Dvar_RegisterEnum_t Dvar_RegisterEnum;
	Dvar_RegisterFloat_t Dvar_RegisterFloat;
	Dvar_RegisterInt_t Dvar_RegisterInt;
	Dvar_RegisterString_t Dvar_RegisterString;
	Dvar_RegisterVec2_t Dvar_RegisterVec2;
	Dvar_RegisterVec4_t Dvar_RegisterVec4;
	Dvar_Reset_t Dvar_Reset;
	Dvar_SetBool_t Dvar_SetBool;
	Dvar_SetCommand_t Dvar_SetCommand;
	Dvar_SetString_t Dvar_SetString;
	Dvar_Sort_t Dvar_Sort;
	Dvar_ValueToString_t Dvar_ValueToString;

	FS_ReadFile_t FS_ReadFile;
	FS_FreeFile_t FS_FreeFile;

	G_RunFrame_t G_RunFrame;

	I_CleanStr_t I_CleanStr;

	Key_KeynumToString_t Key_KeynumToString;

	Live_SyncOnlineDataFlags_t Live_SyncOnlineDataFlags;

	LUI_OpenMenu_t LUI_OpenMenu;

	Menu_IsMenuOpenAndVisible_t Menu_IsMenuOpenAndVisible;

	Material_RegisterHandle_t Material_RegisterHandle;

	NET_StringToAdr_t NET_StringToAdr;

	R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;
	R_AddCmdDrawText_t R_AddCmdDrawText;
	R_AddCmdDrawTextWithCursor_t R_AddCmdDrawTextWithCursor;
	R_RegisterFont_t R_RegisterFont;
	R_TextWidth_t R_TextWidth;

	ScrPlace_GetViewPlacement_t ScrPlace_GetViewPlacement;

	Scr_GetFloat_t Scr_GetFloat;
	Scr_GetNumParam_t Scr_GetNumParam;

	SEH_StringEd_GetString_t SEH_StringEd_GetString;

	SV_GameSendServerCommand_t SV_GameSendServerCommand;
	SV_Loaded_t SV_Loaded;

	SV_StartMap_t SV_StartMap;
	SV_StartMapForParty_t SV_StartMapForParty;

	SV_AddBot_t SV_AddBot;
	SV_BotIsBot_t SV_BotIsBot;
	SV_ExecuteClientCommand_t SV_ExecuteClientCommand;
	SV_FastRestart_t SV_FastRestart;
	SV_GetGuid_t SV_GetGuid;
	SV_KickClientNum_t SV_KickClientNum;
	SV_SetConfigstring_t SV_SetConfigstring;
	SV_SpawnTestClient_t SV_SpawnTestClient;

	Sys_IsDatabaseReady2_t Sys_IsDatabaseReady2;
	Sys_Milliseconds_t Sys_Milliseconds;
	Sys_SendPacket_t Sys_SendPacket;

	SwitchToCoreMode_t SwitchToCoreMode;
	SwitchToAliensMode_t SwitchToAliensMode;
	SwitchToSquadVsSquadMode_t SwitchToSquadVsSquadMode;

	UI_LocalizeMapname_t UI_LocalizeMapname;
	UI_LocalizeMapname_t UI_LocalizeGametype;

	int* keyCatchers;

	CmdArgs* cmd_args;
	CmdArgs* sv_cmd_args;
	cmd_function_s** cmd_functions;

	int* dvarCount;
	dvar_t** sortedDvars;

	PlayerKeyState* playerKeys;

	SOCKET* query_socket;

	const char** command_whitelist;

	namespace sp
	{
		gentity_s* g_entities;
	}

	namespace mp
	{
		cg_s* cgArray;

		gentity_s* g_entities;

		int* svs_numclients;
		client_t* svs_clients;

		std::uint32_t* sv_serverId_value;

		int* gameTime;
		int* serverTime;
	}

	int Cmd_Argc()
	{
		return cmd_args->argc[cmd_args->nesting];
	}

	const char* Cmd_Argv(int index)
	{
		return cmd_args->argv[cmd_args->nesting][index];
	}

	int SV_Cmd_Argc()
	{
		return sv_cmd_args->argc[sv_cmd_args->nesting];
	}

	const char* SV_Cmd_Argv(int index)
	{
		return sv_cmd_args->argv[sv_cmd_args->nesting][index];
	}

	namespace environment
	{
		launcher::mode mode = launcher::mode::none;

		launcher::mode get_mode()
		{
			if (mode == launcher::mode::none)
			{
				throw std::runtime_error("Launcher mode not valid. Something must be wrong.");
			}

			return mode;
		}

		bool is_dedi()
		{
			return get_mode() == launcher::mode::server;
		}

		bool is_mp()
		{
			return get_mode() == launcher::mode::multiplayer;
		}

		bool is_sp()
		{
			return get_mode() == launcher::mode::singleplayer;
		}

		void set_mode(const launcher::mode _mode)
		{
			mode = _mode;
		}

		void initialize()
		{
			Sys_ShowConsole = Sys_ShowConsole_t(SELECT_VALUE(0x14043E650, 0x140503130));
			Conbuf_AppendText = Conbuf_AppendText_t(SELECT_VALUE(0x14043DDE0, 0x1405028C0));

			Com_Frame_Try_Block_Function = Com_Frame_Try_Block_Function_t(SELECT_VALUE(0x1403BC980, 0x1404131A0));
			Com_Parse = Com_Parse_t(SELECT_VALUE(0, 0x1404F50E0));
			Com_Error = Com_Error_t(SELECT_VALUE(0x1403BBFF0, 0x140412740));
			Com_Quit = Com_Quit_t(SELECT_VALUE(0x1403BDDD0, 0x140414920));
			Com_GetCurrentCoDPlayMode = Com_GetCurrentCoDPlayMode_t(SELECT_VALUE(0, 0x1404f6140));
			Com_SetSlowMotion = Com_SetSlowMotion_t(SELECT_VALUE(0, 0x1404158C0));

			Cbuf_AddText = Cbuf_AddText_t(SELECT_VALUE(0x1403B3050, 0x1403F6B50));
			Cbuf_ExecuteBufferInternal = Cbuf_ExecuteBufferInternal_t(SELECT_VALUE(0x1403B3160, 0x1403F6C60));

			CG_GameMessage = CG_GameMessage_t(SELECT_VALUE(0x1401F2E20, 0x140271320));

			CL_IsCgameInitialized = CL_IsCgameInitialized_t(SELECT_VALUE(0x140234DA0, 0x1402B9A70));

			Cmd_AddCommandInternal = Cmd_AddCommandInternal_t(SELECT_VALUE(0x1403B3570, 0x1403F7070));
			Cmd_ExecuteSingleCommand = Cmd_ExecuteSingleCommand_t(SELECT_VALUE(0x1403B3B10, 0x1403F7680));

			Dvar_FindVar = Dvar_FindVar_t(SELECT_VALUE(0x140429E70, 0x1404ECB60));
			Dvar_GetCombinedString = Dvar_GetCombinedString_t(SELECT_VALUE(0x1403BFD80, 0x140416B30));
			Dvar_GetVariantStringWithDefault = Dvar_GetVariantStringWithDefault_t(
				SELECT_VALUE(0x14042A240, 0x1404ECF90));
			Dvar_RegisterBool = Dvar_RegisterBool_t(SELECT_VALUE(0x14042AF10, 0x1404EDD60));
			Dvar_RegisterEnum = Dvar_RegisterEnum_t(SELECT_VALUE(0x14042B220, 0x1404EE070));
			Dvar_RegisterFloat = Dvar_RegisterFloat_t(SELECT_VALUE(0x14042B330, 0x1404EE180));
			Dvar_RegisterInt = Dvar_RegisterInt_t(SELECT_VALUE(0x14042B420, 0x1404EE270));
			Dvar_RegisterString = Dvar_RegisterString_t(SELECT_VALUE(0x14042B7A0, 0x1404EE660));
			Dvar_RegisterVec2 = Dvar_RegisterVec2_t(SELECT_VALUE(0x14042B880, 0x1404EE740));
			Dvar_RegisterVec4 = Dvar_RegisterVec4_t(SELECT_VALUE(0x14042BC10, 0x1404EEA50));
			Dvar_Reset = Dvar_Reset_t(SELECT_VALUE(0x14042C150, 0x1404EF020));
			Dvar_SetBool = Dvar_SetBool_t(SELECT_VALUE(0x14042C370, 0x1404EF1A0));
			Dvar_SetCommand = Dvar_SetCommand_t(SELECT_VALUE(0x14042C8E0, 0x1404EF790));
			Dvar_SetString = Dvar_SetString_t(SELECT_VALUE(0x14042D6E0, 0x1404F08E0));
			Dvar_Sort = Dvar_Sort_t(SELECT_VALUE(0x14042DEF0, 0x1404F1210));
			Dvar_ValueToString = Dvar_ValueToString_t(SELECT_VALUE(0x14042E710, 0x1404F1A30));

			G_RunFrame = G_RunFrame_t(SELECT_VALUE(0x0, 0x1403A05E0));

			I_CleanStr = I_CleanStr_t(SELECT_VALUE(0x140432460, 0x1404F63C0));

			Key_KeynumToString = Key_KeynumToString_t(SELECT_VALUE(0x14023D9A0, 0x1402C40E0));

			FS_ReadFile = FS_ReadFile_t(SELECT_VALUE(0x14041D0B0, 0x1404DE900));
			FS_FreeFile = FS_FreeFile_t(SELECT_VALUE(0x14041D0A0, 0x1404DE8F0));

			Live_SyncOnlineDataFlags = Live_SyncOnlineDataFlags_t(SELECT_VALUE(0, 0x1405ABF70));

			LUI_OpenMenu = LUI_OpenMenu_t(SELECT_VALUE(0x0, 0x1404B3610));

			Menu_IsMenuOpenAndVisible = Menu_IsMenuOpenAndVisible_t(SELECT_VALUE(0x0, 0x1404B38A0));

			Material_RegisterHandle = Material_RegisterHandle_t(SELECT_VALUE(0x140523D90, 0x1405F0E20));

			NET_StringToAdr = NET_StringToAdr_t(SELECT_VALUE(0, 0x14041D870));

			R_AddCmdDrawStretchPic = R_AddCmdDrawStretchPic_t(SELECT_VALUE(0x140234460, 0x140600BE0));
			R_AddCmdDrawText = R_AddCmdDrawText_t(SELECT_VALUE(0x140533E40, 0x140601070));
			R_AddCmdDrawTextWithCursor = R_AddCmdDrawTextWithCursor_t(SELECT_VALUE(0x140534170, 0x1406013A0));
			R_RegisterFont = R_RegisterFont_t(SELECT_VALUE(0x1405130B0, 0x1405DFAC0));
			R_TextWidth = R_TextWidth_t(SELECT_VALUE(0x140513390, 0x1405DFDB0));

			ScrPlace_GetViewPlacement = ScrPlace_GetViewPlacement_t(SELECT_VALUE(0x14024D150, 0x1402F6D40));

			Scr_GetFloat = Scr_GetFloat_t(SELECT_VALUE(0, 0x140438D60));
			Scr_GetNumParam = Scr_GetNumParam_t(SELECT_VALUE(0, 0x140438EC0));

			SEH_StringEd_GetString = SEH_StringEd_GetString_t(SELECT_VALUE(0x0, 0x1404A5F60));

			SV_GameSendServerCommand = SV_GameSendServerCommand_t(SELECT_VALUE(0x140490F40, 0x1404758C0));
			SV_Loaded = SV_Loaded_t(SELECT_VALUE(0x140491820, 0x1404770C0));
			SV_StartMap = SV_StartMap_t(SELECT_VALUE(0, 0x140470170));
			SV_StartMapForParty = SV_StartMapForParty_t(SELECT_VALUE(0, 0x1404702F0));
			SV_AddBot = SV_AddBot_t(SELECT_VALUE(0, 0x140470920));
			SV_BotIsBot = SV_BotIsBot_t(SELECT_VALUE(0, 0x140461340));
			SV_ExecuteClientCommand = SV_ExecuteClientCommand_t(SELECT_VALUE(0, 0x140472430));
			SV_FastRestart = SV_FastRestart_t(SELECT_VALUE(0x14048B890, 0x14046F440));
			SV_GetGuid = SV_GetGuid_t(SELECT_VALUE(0, 0x140475990));
			SV_KickClientNum = SV_KickClientNum_t(SELECT_VALUE(0, 0x14046F730));
			SV_SetConfigstring = SV_SetConfigstring_t(SELECT_VALUE(0, 0x140477450));
			SV_SpawnTestClient = SV_SpawnTestClient_t(SELECT_VALUE(0, 0x1404740A0));

			Sys_IsDatabaseReady2 = Sys_IsDatabaseReady2_t(SELECT_VALUE(0x1403C2D40, 0x140423920));
			Sys_Milliseconds = Sys_Milliseconds_t(SELECT_VALUE(0x14043D2A0, 0x140501CA0));
			Sys_SendPacket = Sys_SendPacket_t(SELECT_VALUE(0x14043D000, 0x140501A00));

			SwitchToCoreMode = SwitchToCoreMode_t(SELECT_VALUE(0, 0x1401FA4A0));
			SwitchToSquadVsSquadMode = SwitchToSquadVsSquadMode_t(SELECT_VALUE(0, 0x1401FA500));
			SwitchToAliensMode = SwitchToAliensMode_t(SELECT_VALUE(0, 0x1401FA4D0));

			UI_LocalizeMapname = UI_LocalizeMapname_t(SELECT_VALUE(0, 0x1404B96D0));
			UI_LocalizeGametype = UI_LocalizeMapname_t(SELECT_VALUE(0, 0x1404B90F0));

			keyCatchers = reinterpret_cast<int*>(SELECT_VALUE(0x1417CF6E0, 0x1419E1ADC));

			cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0x144CE7F70, 0x144518480));
			sv_cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0x144CE8020, 0x144518530));
			cmd_functions = reinterpret_cast<cmd_function_s**>(SELECT_VALUE(0x144CE80C8, 0x1445185D8));

			dvarCount = reinterpret_cast<int*>(SELECT_VALUE(0x1458CBA3C, 0x1478EADF4));
			sortedDvars = reinterpret_cast<dvar_t**>(SELECT_VALUE(0x1458CBA60, 0x1478EAE10));

			playerKeys = reinterpret_cast<PlayerKeyState*>(SELECT_VALUE(0x14164138C, 0x1419DEABC));

			query_socket = reinterpret_cast<SOCKET*>(SELECT_VALUE(0, 0x147AD1A78));

			command_whitelist = reinterpret_cast<const char**>(SELECT_VALUE(0x14086AA70, 0x1409E3AB0));

			if (is_sp())
			{
				sp::g_entities = reinterpret_cast<sp::gentity_s*>(0x143C91600);
			}
			else
			{
				mp::cgArray = reinterpret_cast<mp::cg_s*>(0x14176EC00);

				mp::g_entities = reinterpret_cast<mp::gentity_s*>(0x14427A0E0);

				mp::svs_numclients = reinterpret_cast<int*>(0x14647B28C);
				mp::svs_clients = reinterpret_cast<mp::client_t*>(0x14647B290);

				mp::sv_serverId_value = reinterpret_cast<std::uint32_t*>(0x144DF9478);

				mp::gameTime = reinterpret_cast<int*>(0x1443F4B6C);
				mp::serverTime = reinterpret_cast<int*>(0x14647B280);
			}
		}
	}
}
