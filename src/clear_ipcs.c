#include "../include/lem-ipc.h"

void
clear_ipcs()
{
	if (!data)
		return;
	sem_wait(player.sem);
	data->player_count--;
	data->team_player[player.team_id]--;
	sem_post(player.sem);
	sem_close(player.sem);
	if (data->player_count <= 0) {
		sem_unlink(SEM_KEY);
		mq_unlink(MSGQ_KEY);
		shm_unlink(SHM_KEY);
	}
	munmap(data, sizeof(t_data));
}
