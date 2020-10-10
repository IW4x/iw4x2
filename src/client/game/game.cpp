#include <std_include.hpp>
#include "game.hpp"

namespace game
{
	Sys_ShowConsole_t Sys_ShowConsole;

	Com_Frame_Try_Block_Function_t Com_Frame_Try_Block_Function;
	Com_Error_t Com_Error;

	Conbuf_AppendText_t Conbuf_AppendText;

	Cbuf_AddText_t Cbuf_AddText;

	CG_GameMessage_t CG_GameMessage;

	CL_IsCgameInitialized_t CL_IsCgameInitialized;

	Cmd_AddCommandInternal_t Cmd_AddCommandInternal;
	Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

	Dvar_FindVar_t Dvar_FindVar;
	Dvar_RegisterBool_t Dvar_RegisterBool;
	Dvar_RegisterEnum_t Dvar_RegisterEnum;
	Dvar_RegisterFloat_t Dvar_RegisterFloat;
	Dvar_RegisterInt_t Dvar_RegisterInt;
	Dvar_RegisterString_t Dvar_RegisterString;
	Dvar_RegisterVec2_t Dvar_RegisterVec2;
	Dvar_RegisterVec4_t Dvar_RegisterVec4;
	Dvar_Sort_t Dvar_Sort;
	Dvar_ValueToString_t Dvar_ValueToString;

	G_RunFrame_t G_RunFrame;

	LUI_OpenMenu_t LUI_OpenMenu;

	Material_RegisterHandle_t Material_RegisterHandle;

	NET_StringToAdr_t NET_StringToAdr;

	R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;
	R_AddCmdDrawText_t R_AddCmdDrawText;
	R_AddCmdDrawTextWithCursor_t R_AddCmdDrawTextWithCursor;
	R_RegisterFont_t R_RegisterFont;
	R_TextWidth_t R_TextWidth;

	ScrPlace_GetViewPlacement_t ScrPlace_GetViewPlacement;

	SEH_StringEd_GetString_t SEH_StringEd_GetString;

	SV_GameSendServerCommand_t SV_GameSendServerCommand;
	SV_Loaded_t SV_Loaded;

	Sys_Milliseconds_t Sys_Milliseconds;
	Sys_SendPacket_t Sys_SendPacket;

	int* keyCatchers;

	CmdArgs* cmd_args;
	CmdArgs* sv_cmd_args;
	cmd_function_s** cmd_functions;

	int* dvarCount;
	dvar_t** sortedDvars;

	PlayerKeyState* playerKeys;

	SOCKET* query_socket;

	namespace sp
	{
		gentity_s* g_entities;
	}

	namespace mp
	{
		cg_s* cgArray;

		gentity_s* g_entities;
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

	launcher::mode mode = launcher::mode::none;

	launcher::mode get_mode()
	{
		if (mode == launcher::mode::none)
		{
			throw std::runtime_error("Launcher mode not valid. Something must be wrong.");
		}

		return mode;
	}

	namespace environment
	{
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

		void initialize(const launcher::mode _mode)
		{
			mode = _mode;

			Sys_ShowConsole = Sys_ShowConsole_t(SELECT_VALUE(0x14043E650, 0x140503130));
			Conbuf_AppendText = Conbuf_AppendText_t(SELECT_VALUE(0x14043DDE0, 0x1405028C0));

			Com_Frame_Try_Block_Function = Com_Frame_Try_Block_Function_t(SELECT_VALUE(0x1403BC980, 0x1404131A0));
			Com_Error = Com_Error_t(SELECT_VALUE(0x1403BBFF0, 0x140412740));

			Cbuf_AddText = Cbuf_AddText_t(SELECT_VALUE(0x1403B3050, 0x1403F6B50));

			CG_GameMessage = CG_GameMessage_t(SELECT_VALUE(0x1401F2E20, 0x140271320));

			CL_IsCgameInitialized = CL_IsCgameInitialized_t(SELECT_VALUE(0x140234DA0, 0x1402B9A70));

			Cmd_AddCommandInternal = Cmd_AddCommandInternal_t(SELECT_VALUE(0x1403B3570, 0x1403F7070));
			Cmd_ExecuteSingleCommand = Cmd_ExecuteSingleCommand_t(SELECT_VALUE(0x1403B3B10, 0x1403F7680));

			Dvar_FindVar = Dvar_FindVar_t(SELECT_VALUE(0x140429E70, 0x1404ECB60));
			Dvar_RegisterBool = Dvar_RegisterBool_t(SELECT_VALUE(0x14042AF10, 0x1404EDD60));
			Dvar_RegisterEnum = Dvar_RegisterEnum_t(SELECT_VALUE(0x14042B220, 0x1404EE070));
			Dvar_RegisterFloat = Dvar_RegisterFloat_t(SELECT_VALUE(0x14042B330, 0x1404EE180));
			Dvar_RegisterInt = Dvar_RegisterInt_t(SELECT_VALUE(0x14042B420, 0x1404EE270));
			Dvar_RegisterString = Dvar_RegisterString_t(SELECT_VALUE(0x14042B7A0, 0x1404EE660));
			Dvar_RegisterVec2 = Dvar_RegisterVec2_t(SELECT_VALUE(0x14042B880, 0x1404EE740));
			Dvar_RegisterVec4 = Dvar_RegisterVec4_t(SELECT_VALUE(0x14042BC10, 0x1404EEA50));
			Dvar_Sort = Dvar_Sort_t(SELECT_VALUE(0x14042DEF0, 0x1404F1210));
			Dvar_ValueToString = Dvar_ValueToString_t(SELECT_VALUE(0x14042E710, 0x1404F1A30));

			G_RunFrame = G_RunFrame_t(SELECT_VALUE(0x0, 0x1403A05E0));

			LUI_OpenMenu = LUI_OpenMenu_t(SELECT_VALUE(0x0, 0x1404B3610));

			Material_RegisterHandle = Material_RegisterHandle_t(SELECT_VALUE(0x140523D90, 0x1405F0E20));

			NET_StringToAdr = NET_StringToAdr_t(SELECT_VALUE(0, 0x14041D870));

			R_AddCmdDrawStretchPic = R_AddCmdDrawStretchPic_t(SELECT_VALUE(0x140234460, 0x140600BE0));
			R_AddCmdDrawText = R_AddCmdDrawText_t(SELECT_VALUE(0x140533E40, 0x140601070));
			R_AddCmdDrawTextWithCursor = R_AddCmdDrawTextWithCursor_t(SELECT_VALUE(0x140534170, 0x1406013A0));
			R_RegisterFont = R_RegisterFont_t(SELECT_VALUE(0x1405130B0, 0x1405DFAC0));
			R_TextWidth = R_TextWidth_t(SELECT_VALUE(0x140513390, 0x1405DFDB0));

			ScrPlace_GetViewPlacement = ScrPlace_GetViewPlacement_t(SELECT_VALUE(0x14024D150, 0x1402F6D40));

			SEH_StringEd_GetString = SEH_StringEd_GetString_t(SELECT_VALUE(0x0, 0x1404A5F60));

			SV_GameSendServerCommand = SV_GameSendServerCommand_t(SELECT_VALUE(0x140490F40, 0x1404758C0));
			SV_Loaded = SV_Loaded_t(SELECT_VALUE(0x140491820, 0x1404770C0));

			Sys_Milliseconds = Sys_Milliseconds_t(SELECT_VALUE(0x14043D2A0, 0x140501CA0));
			Sys_SendPacket = Sys_SendPacket_t(SELECT_VALUE(0x14043D000, 0x140501A00));

			keyCatchers = reinterpret_cast<int*>(SELECT_VALUE(0x1417CF6E0, 0x1419E1ADC));

			cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0x144CE7F70, 0x144518480));
			sv_cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0x144CE8020, 0x144518530));
			cmd_functions = reinterpret_cast<cmd_function_s**>(SELECT_VALUE(0x144CE80C8, 0x1445185D8));

			dvarCount = reinterpret_cast<int*>(SELECT_VALUE(0x1458CBA3C, 0x1478EADF4));
			sortedDvars = reinterpret_cast<dvar_t**>(SELECT_VALUE(0x1458CBA60, 0x1478EAE10));

			playerKeys = reinterpret_cast<PlayerKeyState*>(SELECT_VALUE(0x14164138C, 0x1419DEABC));

			query_socket = reinterpret_cast<SOCKET*>(SELECT_VALUE(0, 0x147AD1A78));

			if (is_sp())
			{
				sp::g_entities = reinterpret_cast<sp::gentity_s*>(0x143C91600);
			}
			else if (is_mp())
			{
				mp::cgArray = reinterpret_cast<mp::cg_s*>(0x14176EC00);

				mp::g_entities = reinterpret_cast<mp::gentity_s*>(0x14427A0E0);
			}
		}
	}
}
