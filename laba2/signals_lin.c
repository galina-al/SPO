#include "signals.h"


int kill(pid_t Pid, int Signal);

int usleep(unsigned int usec);


void addProcess(struct Cell **head)
{
	struct ProcessInfo temp;
	temp.id = fork();
	key_t key = ftok("main.c", 228);
	int SemID = semget(key,0,0666 );
	static struct sembuf lock, rel;
	lock.sem_num=0;
	lock.sem_op=1; 
	rel.sem_num=0;
	rel.sem_op=-1;
	switch(temp.id)
	{
		case -1:
		{
			printf("Error!");
			exit(1);
		}
		break;

		case 0:
		{
			while(1)
			{
			semop(SemID,&lock, 1);	//блокировать
			printf("PID: %d\n",getpid());
			usleep(1000000);
			semop(SemID,&rel, 1);	//разблокировать
			}
		}
		break;
		
		default:
		{
			push(head,temp);
		}
		break;
	}
}

void deleteOneProcess(struct ProcessInfo info)
{
	kill(info.id, SIGKILL);
}

void deleteAll(struct Cell **head)
{
	while(*head)	
	kill(pop(head).id,SIGKILL);
}


int get_button()
{
	struct termios old, new;
	char ch;
	tcgetattr(0, &old);
	new = old;
	// перевод в неканонический режим (чтобы не ждать нажатия интера)
	new.c_lflag &= ~(ICANON | ECHO);  
	//new.c_lflag &= (~ICANON);// откл канон режим
	//new.c_lflag &= (ECHO); // отбразить
	tcsetattr(0, TCSANOW, &new);
	ch = getchar();
	tcsetattr(0, TCSANOW, &old);
	return ch;
}
void Init()
{
	key_t key = ftok("main.c", 228);
	int SemID = semget(key,1,0666 | IPC_CREAT);
	semctl(SemID, 0, SETVAL,0);
}
