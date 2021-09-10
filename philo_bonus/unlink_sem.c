#include "philolib.h"

int	main()
{
	sem_t	*semaphore;
	sem_t	*die_sem;

	semaphore = sem_open("forks", O_RDWR);
	die_sem = sem_open("die", O_RDWR);
	if (semaphore == SEM_FAILED)
	{
		printf("sem_open failed unlink.c\n");
	}
	if (sem_unlink("forks") < 0)
		printf("sem_unlink failed\n");
	if (die_sem == SEM_FAILED)
	{
		printf("sem_open failed unlink.c\n");
	}
	if (sem_unlink("die") < 0)
		printf("sem_unlink failed\n");

}