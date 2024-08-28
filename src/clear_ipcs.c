#include "../include/lem-ipc.h"

extern t_data	*data;

void
clear_ipcs()
{
	if (!data)
		return;
	sem_wait(data->sem);
	data->player_count--;
	sem_post(data->sem);
	if (data->player_count <= 0) {
		sem_unlink(SEM_KEY);
		mq_unlink(MSGQ_KEY);
		shm_unlink(SHM_KEY);
	}
	munmap(data, sizeof(t_data));
}
