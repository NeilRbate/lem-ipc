#include "../include/lem-ipc.h"

int
clear_ipcs(t_data *data)
{
	ft_printf("sem_id -> %d, shm_id -> %d, msgq_id -> %d\n"
			, data->sem, data->shm_fd, data->msgq);
	
	if (data->sem != NULL)
		sem_close(data->sem);
	if (data->msgq != 0)
		mq_close(data->msgq);
	if (data->shm_fd != -1) {
		close(data->shm_fd);
		shm_unlink(SHM_KEY);
	}
	return 0;
}
