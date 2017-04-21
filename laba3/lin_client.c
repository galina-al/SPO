#include "kanal.h"
#define BUFFER_SIZE 512

void connecting(struct Data *data)
{	
	key_t key = ftok("server.c", 228);

	data->semid = semget(key, 0, 0666);

	data->lock_res.sem_num = 0;	
	data->lock_res.sem_op = -1;	
	data->rel_res.sem_num = 0;	
	data->rel_res.sem_op = 1;
	data->lock_res.sem_flg = IPC_NOWAIT;
	data->rel_res.sem_flg = IPC_NOWAIT;

	printf("Connected to server.\n");
	semop(data->semid, &data->lock_res, 1);
	
	data->fd_fifo = open("fifo", O_WRONLY);
	write(data->fd_fifo,"Client connected.\n",BUFFER_SIZE);	
	close(data->fd_fifo);	
	semop(data->semid, &data->lock_res, 1);

}



void run(struct Data *data)
{	
	char buffer[BUFFER_SIZE];
	int k;
	while(1)	
	{		
		data->fd_fifo = open("fifo", O_RDONLY);
		if(read(data->fd_fifo, &buffer, BUFFER_SIZE))
		{
			puts(buffer);			
		}
		close(data->fd_fifo);
		semop(data->semid, &data->lock_res, 1);

		data->fd_fifo = open("fifo", O_RDONLY);
		if(read(data->fd_fifo, &buffer, BUFFER_SIZE))
		{
			close(data->fd_fifo);
			if(!strcmp(buffer, "exit\0"))	
			{
				clean(data);	
				break;
			}
			else 	
			{		
				puts(buffer);
				data->fd_fifo = open("fifo", O_WRONLY);
				if(!write(data->fd_fifo,"the client has received a message",BUFFER_SIZE))
				{
					break;
				}	
				close(data->fd_fifo);		
			}	
		}
		semop(data->semid, &data->rel_res, 1);	

		data->fd_fifo = open("fifo", O_WRONLY);
		if(!write(data->fd_fifo,"Client ready\n",BUFFER_SIZE))
		{
			break;
		}	
		close(data->fd_fifo);
		semop(data->semid, &data->lock_res, 1);
		
		fflush(stdin);
		fgets(buffer,BUFFER_SIZE, stdin);
		k = strlen(buffer);
		buffer[k-1] = '\0';

		data->fd_fifo = open("fifo", O_WRONLY);
		if(!write(data->fd_fifo,buffer,BUFFER_SIZE))
		{
			break;
		}	
		close(data->fd_fifo);	
		semop(data->semid, &data->lock_res, 1);

		if(!strcmp(buffer, "exit\0"))	
			{
				clean(data);	
				break;
			}

		data->fd_fifo = open("fifo", O_RDONLY);
		if(read(data->fd_fifo, &buffer, BUFFER_SIZE))
		{
			puts(buffer);
		}	
		close(data->fd_fifo);
		semop(data->semid, &data->rel_res, 1);
			
	}
}	

void clean(struct Data *data)
{
	semctl(data->semid, 0, IPC_RMID);
	unlink("fifo");
}
