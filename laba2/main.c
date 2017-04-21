#include "signals.h"

int main()
{
	struct Cell **head = (struct Cell**)malloc(sizeof(struct Cell*));
	*head = NULL;
	while(1)
	{
		printf("\nEnter action(+/-/q): \n");
		switch(get_button())
		{
			case '+':
				addProcess(head);	
			break;
			case '-':
				if(*head)
				{
					deleteOneProcess(pop(head));
					printf("One process delete!\n");
				}
			break;
			case 'q':
				{
					deleteAll(head);
					free(head);
					printf("\nAll process delete!\n");
					return 0;
				}
			break;
		}
	}
	return 0;
}	
