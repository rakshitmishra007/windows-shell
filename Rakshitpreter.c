#include<windows.h>
#include<stdio.h>
#include<tchar.h>
#include<tlhelp32.h>
#include<stdlib.h>
#include "dll.h"

typedef char * (*func_ptr)();
func_ptr fptr;

int main()
{
	
	while(1)
	{
		HMODULE hinst;
		HANDLE pipe = CreateNamedPipe("\\\\.\\pipe\\LogPipe", PIPE_ACCESS_DUPLEX, PIPE_WAIT, 1, 1024, 1024, 120 * 1000, NULL);
		
		if(pipe == INVALID_HANDLE_VALUE)
		{
			printf("Error: %d", GetLastError());
			getch();
			return 0;
		}
		char data[1024];
		DWORD numRead;
		
		ConnectNamedPipe(pipe, NULL);
		
		ReadFile(pipe, data, sizeof(data) - 1, &numRead, NULL);
		
		if(numRead > 0)
		{
			if (!strcmp("sysinfo", data))
			{
				hinst =	LoadLibrary("speech.dll");								//take this line common
				fptr = (func_ptr)GetProcAddress(hinst, "system_info");
			}
			else if (!strcmp("idletime", data))
			{
				hinst =	LoadLibrary("speech.dll");
				fptr = (func_ptr)GetProcAddress(hinst, "idletime");
			}
			else if(!strcmp("shutdown", data))
			{
				hinst =	LoadLibrary("speech.dll");
				fptr = (func_ptr)GetProcAddress(hinst, "system_shutdown");
			}
			else if(!strcmp("pwd", data))
			{
				hinst =	LoadLibrary("speech.dll");
				fptr = (func_ptr)GetProcAddress(hinst, "current_dir");
			}
			else if(!strcmp("cd", data)) //Need to modify this to start accepting arguments from command-line.
			{
				char newdir[MAX_PATH];
				SetCurrentDirectory(newdir);
			}
			else if(!strcmp("ps", data))
			{
				hinst =	LoadLibrary("speech.dll");
				fptr = (func_ptr)GetProcAddress(hinst, "process_list");
			}
			else if(!strcmp("ls", data))
			{
				hinst =	LoadLibrary("speech.dll");
				fptr = (func_ptr)GetProcAddress(hinst, "list_files");
			}
			else if(!strcmp("quit", data))
			{
				exit(0);
			}
			else
			{
				hinst =	LoadLibrary("speech.dll");
				fptr = (func_ptr)GetProcAddress(hinst, "unknown_command");
			}
			DWORD numWritten;
			WriteFile(pipe, fptr(), strlen(fptr()), &numWritten, NULL);
			FreeLibrary(hinst);
		}
		
		CloseHandle(pipe);
	}
		
		
}
