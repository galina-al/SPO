#ifndef STACK_H

#define STACK_H



#include <stdlib.h>
#include <stdio.h>

#if _WIN32 || _WIN64

#include <windows.h>


struct ProcessInfo
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION procInfo;
	HANDLE semaphore;
};

#else 
//#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>

struct ProcessInfo
{
	pid_t id;
};

#endif

struct Cell
{
	struct ProcessInfo information;

	struct Cell *next;
};


void push(struct Cell**, struct ProcessInfo);


struct ProcessInfo pop(struct Cell**);



#endif
