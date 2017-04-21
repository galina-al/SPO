#include "signals.h"
#include <conio.h>

void addProcess(struct Cell **head)
{
	struct ProcessInfo temp;
	TCHAR newProcessName[] = TEXT("print.exe");
	ZeroMemory(&temp.startupInfo, sizeof(STARTUPINFO));
	if (CreateProcess(NULL, 
		newProcessName, 
		NULL, 
		NULL, 
		FALSE, 
		0,
		NULL, 
		NULL, 
		&temp.startupInfo,
		&temp.procInfo) == TRUE)
	{
		printf("Add process\n");
		push(head,temp);
	}
	else exit(1);
	
}

void deleteOneProcess(struct ProcessInfo info)
{
	TerminateProcess(info.procInfo.hProcess, 0);
}

void deleteAll(struct Cell **head)
{
	while(*head)
		TerminateProcess(pop(head).procInfo.hProcess,0);
}

int get_button()
{
	return _getch();
}
void Init(struct ProcessInfo* data)
{
	CreateSemaphore(NULL, 0, 1, "Sem");
}
