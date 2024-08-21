#include "../include/lem-ipc.h"

int
clear_ipcs(sem_t *sem_id, int shm_id, mqd_t msgq_id)
{
	ft_printf("sem_id -> %d, shm_id -> %d, msgq_id -> %d\n"
			, sem_id, shm_id, msgq_id);
	if (shm_id != -1)
		shm_unlink(SHM_KEY);
	if (sem_id != NULL)
		sem_close(sem_id);
	if (msgq_id != 0)
		mq_close(msgq_id);
	return 0;
}
