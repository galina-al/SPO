#include "header.h"

int main()
{
	struct Cell **head = (struct Cell**)malloc(sizeof(struct Cell*));
	*head = NULL;

	struct MutexInfo criticalS;
	criticalS.count = 0;
	init(&criticalS);

	printf("Enter action(+/-/q):\n");
	while(1)
	{
		switch(get_button())
		{
			case '+':
			{
				push(head, createNewThread(&criticalS));
				criticalS.count++;

			}
			break;
			case '-':
			{
				if(*head)
				{	
					#if defined(_WIN32) || defined(_WIN64)
					EnterCriticalSection( &cs );
					deleteOneThread(pop(head));	
					printf("\nOne thread is removed!\n");
					LeaveCriticalSection( &cs );
					criticalS.count--;
					#else
					deleteOneThread(pop(head));	
					printf("\nOne thread is removed!\n");
					#endif
				}
			}
			break;
			case 'q':
			{
				deleteAll(head);	
				printf("\nAll (%d) threads are removed!\n", criticalS.count);
				criticalS.count = 0;
				return 0;
			}
			break;
		}
	}
	return 0;
}
