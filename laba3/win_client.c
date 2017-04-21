#include "kanal.h"
#define BUFFER_SIZE 512



void connecting(struct Data *data)
{
	data->semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SemClient"));
	data->channel = CreateFile(TEXT("\\\\.\\pipe\\$MyPipe$"), GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);

	printf("Connected to server.\n");
	ConnectNamedPipe(data->channel,NULL );
	ReleaseSemaphore(data->semaphore, 1, NULL);

}

void run(struct Data *data)
{
	char buffer[BUFFER_SIZE];
	while(1)
	{
		DWORD  dwRead;
		if(ReadFile(data->channel, buffer, 
		BUFFER_SIZE, &dwRead, NULL))
		{
			printf("%s\n", buffer);
		}
		ReleaseSemaphore(data->semaphore, 1, NULL);

		WaitForSingleObject(data->semaphore, INFINITE);

		if(ReadFile(data->channel, buffer, 
		BUFFER_SIZE, &dwRead, NULL))
		{
			if(strcmp(buffer,"exit"))
			{
				printf("%s\n", buffer);
				DWORD dwWritten;
				if(!WriteFile(data->channel, "the client has received a message", 
				BUFFER_SIZE, &dwWritten, NULL))
				{
					break;
				}
			}
			else
				clean(data);
		}
		ReleaseSemaphore(data->semaphore, 1, NULL);

		WaitForSingleObject(data->semaphore, INFINITE);

		DWORD dwWritten1;
		if (!WriteFile( data->channel, "Client ready", BUFFER_SIZE, 
			&dwWritten1, NULL))  
		{
			break;
		} 
		ReleaseSemaphore(data->semaphore, 1, NULL);

		WaitForSingleObject(data->semaphore, INFINITE);

		fflush(stdin);
		gets(buffer);
		DWORD  dwWritten2;
		if(!WriteFile(data->channel, buffer, BUFFER_SIZE, 
  				&dwWritten2, NULL))
		{
			break;
		}
		ReleaseSemaphore(data->semaphore, 1, NULL);
		
		WaitForSingleObject(data->semaphore, INFINITE);

		if(ReadFile(data->channel, buffer, 
		BUFFER_SIZE, &dwRead, NULL))
		{
			printf("%s\n", buffer);
		}
	}
}	

void clean(struct Data *data)
{
	CloseHandle(data->channel);
	CloseHandle(data->semaphore);
}

