#include "signals.h"
#include "stack.h"

int main()
{
	printf("Print");
	struct ProcessInfo data;
	data.semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("Sem"));
	while(1)
	{
		ReleaseSemaphore(data.semaphore,1, NULL);
		printf("\nID process: %d\n",GetCurrentProcessId());
		Sleep(1000);
		ReleaseSemaphore(data.semaphore,0, NULL);
		WaitForSingleObject(data.semaphore, INFINITE);
	}
	return 0;
}
