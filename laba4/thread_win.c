#include "header.h"




DWORD WINAPI printID()

{

	while(1)
	
	{


	
		EnterCriticalSection( &cs );
		printf("Thread id: %d\n",(int)GetCurrentThreadId());
			
		LeaveCriticalSection( &cs );
		Sleep(1000);
	}
	
	return 0;

}


int get_button()

{
	
	return getch();

}




void deleteOneThread(struct ThreadInfo info)

{
	TerminateThread(info.thread,0);	
}



struct ThreadInfo createNewThread(struct MutexInfo *criticalS)

{

	struct ThreadInfo info;
	
	info.thread = CreateThread(NULL, 0, printID, 0, 0, NULL);

	return info;

}



void init(struct MutexInfo *criticalS)

{

	InitializeCriticalSection( &cs );
}



void deleteAll(struct Cell **head)

{
	
	while(*head)
	
		deleteOneThread(pop(head));
	DeleteCriticalSection(&cs);
}
