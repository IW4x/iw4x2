#pragma once

// MP: 0x0B459A00
// SP: 0x079C6A00
#define BINARY_PAYLOAD_SIZE 0x0B500000

#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4127)
#pragma warning(disable: 4244)
#pragma warning(disable: 4458)
#pragma warning(disable: 4702)
#pragma warning(disable: 4996)
#pragma warning(disable: 5054)
#pragma warning(disable: 6011)
#pragma warning(disable: 6297)
#pragma warning(disable: 6385)
#pragma warning(disable: 6386)
#pragma warning(disable: 6387)
#pragma warning(disable: 26110)
#pragma warning(disable: 26451)
#pragma warning(disable: 26444)
#pragma warning(disable: 26451)
#pragma warning(disable: 26489)
#pragma warning(disable: 26495)
#pragma warning(disable: 26498)
#pragma warning(disable: 26812)
#pragma warning(disable: 28020)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mshtml.h>
#include <mshtmhst.h>
#include <ExDisp.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <corecrt_io.h>
#include <fcntl.h>
#include <shellapi.h>
#include <csetjmp>
#include <ShlObj.h>
#include <winternl.h>
#include <versionhelpers.h>
#include <Psapi.h>
#include <Urlmon.h>
#include <atlbase.h>
#include <iphlpapi.h>

// min and max is required by gdi, therefore NOMINMAX won't work
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <map>
#include <atomic>
#include <vector>
#include <mutex>
#include <queue>
#include <regex>
#include <chrono>
#include <thread>
#include <fstream>
#include <utility>
#include <filesystem>
#include <functional>
#include <sstream>

#include <zlib.h>
#include <gsl/gsl>
#include <udis86.h>
#include <MinHook.h>
#include <tomcrypt.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <asmjit/core/jitruntime.h>
#include <asmjit/x86/x86assembler.h>

#include "proto/network.pb.h"

#pragma warning(pop)
#pragma warning(disable: 4100)

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment( lib, "Urlmon.lib" )
#pragma comment(lib, "IPHLPAPI.lib")

#include "resource.hpp"

using namespace std::literals;
