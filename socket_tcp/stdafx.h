// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <vector>
#include <string>

#include <stdio.h>
#include <tchar.h>
#include <signal.h>
#include <stdlib.h>

#include <WinSock2.h>
#include <Strsafe.h>

//#include "Base16.h"

#pragma comment( lib, "ws2_32.lib"  )
#pragma comment(lib, "Debug/DBConnector.lib")
#define snprintf _snprintf_s 
using namespace std;
// TODO: reference additional headers your program requires here

#define IP_ADD_SOURCE_MEMBERSHIP   25
#define IP_DROP_SOURCE_MEMBERSHIP 26