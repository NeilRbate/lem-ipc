#include "../include/lem-ipc.h"

sem_t
*init_sem()
{
	/* Create shared semaphore and return it */
	sem_t	*sem = NULL;

	sem = sem_open(SEM_KEY, O_RDWR);
	if (sem != SEM_FAILED) {
		return sem;
	}

	sem = sem_open(SEM_KEY, O_CREAT, 
			S_IRUSR | S_IWUSR, 1);
	if (sem == SEM_FAILED) {
		perror("semaphore error");
		exit(EXIT_FAILURE);
	}

	return sem;
}
