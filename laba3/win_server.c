#include "kanal.h"
#define BUFFER_SIZE 512



void connecting(struct Data *data)
{
	data->semaphore = CreateSemaphore(NULL, 0, 1, "SemServer");

	data->channel = CreateNamedPipe(TEXT("\\\\.\\pipe\\$MyPipe$"), PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES, 100, 100, NMPWAIT_USE_DEFAULT_WAIT, NULL);

	printf("The server is waiting for connection with a client.\n");

	ConnectNamedPipe(data->channel,NULL );
	printf("Client connected\n");		
}

void run(struct Data *data)
{
	char buffer[BUFFER_SIZE];	
	while(1)
	{
		DWORD dwWritten; 
		if (!WriteFile( data->channel, "Server ready", BUFFER_SIZE, 
			&dwWritten, NULL))  
		{
			break;
		} 
		ReleaseSemaphore(data->semaphore, 1, NULL);

		WaitForSingleObject(data->semaphore, INFINITE);

		fflush(stdin);
		gets(buffer);
		DWORD dwWritten1;
		if(!WriteFile(data->channel, buffer, BUFFER_SIZE, 
  				&dwWritten1, NULL))
		{
			break;
		}
		ReleaseSemaphore(data->semaphore, 1, NULL);

		WaitForSingleObject(data->semaphore, INFINITE);

		DWORD dwRead;
		if(ReadFile(data->channel, buffer, BUFFER_SIZE,
			&dwRead, NULL))
		{
			printf("%s\n", buffer);
		}
		ReleaseSemaphore(data->semaphore, 1, NULL);
		
		WaitForSingleObject(data->semaphore, INFINITE);
		
		if(ReadFile(data->channel, buffer, BUFFER_SIZE,
			&dwRead, NULL))
		{
			printf("%s\n", buffer);
		}
		ReleaseSemaphore(data->semaphore, 1, NULL);

		WaitForSingleObject(data->semaphore, INFINITE);
		
		if(ReadFile(data->channel, buffer, BUFFER_SIZE,
			&dwRead, NULL))
		{
			if(strcmp(buffer,"exit"))
			{
				printf("%s\n", buffer);
				if(!WriteFile(data->channel, "the server has received a message", 
				BUFFER_SIZE, &dwWritten, NULL))
				{
					break;
				}
			}
			else
				clean(data);
		}
		ReleaseSemaphore(data->semaphore, 1, NULL);
		
	}
}	

void clean(struct Data *data)
{
	CloseHandle(data->channel);
	CloseHandle(data->semaphore);
}
